/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjarnac <pjarnac@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 14:33:43 by pjarnac           #+#    #+#             */
/*   Updated: 2025/03/10 14:33:43 by pjarnac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>

#include "context.h"
#include "command.h"
#include "parsing.h"
#include "libft.h"
#include "utils.h"
#include "errors.h"

static void	free_args(void *p)
{
	char	*str;

	str = *(char **)p;
	free(str);
}

static void	free_cmds(void *p)
{
	t_cmd	*cmd;

	cmd = (t_cmd *)p;
	if (cmd->args)
		vct_destroy(cmd->args);
}

static void	print_cmd(t_cmd *cmd)
{
	int	i = 0;
	int j;

	while (i < vct_size(cmd))
	{
		printf("{\nPath: %s,\noutput: %d, %s,\ninput: %d, %s,\nArgs: "
			, cmd[i].path, cmd[i].output.op, cmd[i].output.path, cmd[i].input.op,
			cmd[i].input.path);
		j = 0;
		while (j < vct_size(cmd[i].args))
		{
			printf("%s, ", cmd[i].args[j]);
			j++;
		}
		printf("\n},\n");
		i++;
	}
}

static int32_t	process_token(t_token *token, t_cmd *cmd)
{
	if (token->type == COMMAND)
	{
		if (search_path(token->txt, cmd->path) != 0)
			return (-1);
		if (vct_insert(&cmd->args, &(char *){ft_strdup(cmd->path)}, 0) == -1)
			return (-1);
	}
	else if (ROUT <= token->type && token->type <= ROUTAPP)
	{
		if (check_file_create((token + 1)->txt) != 0)
			return (INVALID_FILE);
		cmd->output.op = token->type;
		ft_strlcpy(cmd->output.path, (token + 1)->txt, PATH_MAX);
	}
	else if (token->type == RIN)
	{
		if (access((token + 1)->txt, R_OK) != 0)
			return (p_error((token + 1)->txt, 0, 0), INVALID_FILE);
		cmd->input.op = token->type;
		ft_strlcpy(cmd->input.path, (token + 1)->txt, PATH_MAX);
	}
	else if (token->type == HEREDOC)
	{
		cmd->input.op = token->type;
		ft_strlcpy(cmd->input.path, (token + 1)->txt, PATH_MAX);
	}
	else if (token->type == ARG)
		if (vct_insert(&cmd->args, &(char *){ft_strdup(token->txt)},
			(int32_t)vct_size(cmd->args) - 1) == -1)
			return (-1);
	return (0);
}

static int32_t	add_cmd(t_cmd **cmd)
{
	t_cmd	new_cmd;

	ft_bzero(&new_cmd, sizeof (new_cmd));
	new_cmd.args = vct_create(sizeof (char *), free_args, 0);
	if (!new_cmd.args)
		return (-1);
	if (vct_add(&new_cmd.args, &(char *){0}))
		return (-1);
	if (vct_add(cmd, &new_cmd) != 0)
		return (-1);
	return (0);
}

static int32_t	build_cmds(t_token *tokens, t_cmd **cmd, t_context *ctx)
{
	int32_t			i;
	int32_t			j;
	int32_t			res;

	*cmd = vct_create(sizeof (t_cmd), free_cmds, 0);
	if (!*cmd)
		return (-1);
	j = -1;
	i = -1;
	while (++i < vct_size(tokens))
	{
		if (i == 0 || tokens[i].type == PIPE)
		{
			if (add_cmd(cmd) != 0)
				return (vct_destroy(*cmd), -1);
			j++;
		}
		res = process_token(&tokens[i], *cmd + j);
		if (res != 0)
			return (vct_destroy(*cmd), res);
	}
	print_cmd(*cmd);
	return (0);
}

int32_t	parse(char *str, t_cmd **cmd, t_context *ctx)
{
	char	**args;
	t_token	*tokens;
	int32_t	res;

	res = tokenize(&args, str);
	if (res != 0)
		return (res);
	res = lexer(&tokens, args);
	free_split(args);
	if (res != 0)
		return (res);
	res = build_cmds(tokens, cmd, ctx);
	vct_destroy(tokens);
	if (res != 0)
		return (res);
	return (0);
}
