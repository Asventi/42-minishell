/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nseon <nseon@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 14:33:43 by pjarnac           #+#    #+#             */
/*   Updated: 2025/03/26 11:02:54 by nseon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#include "context.h"
#include "command.h"
#include "parsing.h"
#include "libft.h"
#include "utils.h"
#include "errors.h"
#include "redirect.h"
#include "signals.h"

static int32_t	set_cmd(t_token *tk, t_cmd *cmd, t_context *ctx)
{
	if (tk->type == COMMAND)
	{
		if (search_path(tk->txt, cmd->path, ctx) != 0)
			return (-1);
		if (vct_insert(&cmd->args, &(char *){ft_strdup(cmd->path)}, 0) == -1)
			return (-1);
	}
	else if (ROUT <= tk->type && tk->type <= ROUTAPP)
	{
		if (cmd->output.op != NONE)
			close(cmd->output.fd);
		cmd->output.fd = open((tk + 1)->txt, O_CREAT | O_WRONLY | (O_TRUNC
					* (tk->type == ROUT) + O_APPEND * (tk->type != ROUT)), OR);
		if (cmd->output.fd == -1)
			return (p_error((tk + 1)->txt, 0, 0), INVALID_FILE);
		cmd->output.op = tk->type;
	}
	else if (tk->type == ARG)
		if (vct_insert(&cmd->args, &(char *){ft_strdup(tk->txt)},
			(int32_t)vct_size(cmd->args) - 1) == -1)
			return (-1);
	return (0);
}

static int32_t	process_token(t_token *token, t_cmd *cmd, t_context *ctx)
{
	int32_t	res;

	res = set_cmd(token, cmd, ctx);
	if (res != 0)
		return (res);
	if (token->type == RIN)
	{
		if (cmd->input.op != NONE)
			close(cmd->input.fd);
		cmd->input.fd = open((token + 1)->txt, O_RDONLY);
		if (cmd->input.fd == -1)
			return (p_error((token + 1)->txt, 0, 0), INVALID_FILE);
		cmd->input.op = token->type;
	}
	else if (token->type == HEREDOC)
	{
		if (cmd->input.op != NONE)
			close(cmd->input.fd);
		cmd->input.fd = heredoc((token + 1)->txt, ctx, (token + 1)->quoted);
		if (cmd->input.fd < 0)
			return (cmd->input.fd);
		cmd->input.op = token->type;
	}
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
	while (++i < (int32_t) vct_size(tokens))
	{
		if (i == 0 || tokens[i].type == PIPE)
		{
			if (add_cmd(cmd) != 0)
				return (vct_destroy(*cmd), -1);
			j++;
		}
		res = process_token(&tokens[i], *cmd + j, ctx);
		if (res != 0)
			return (vct_destroy(*cmd), res);
	}
	return (0);
}

int32_t	parse(char *str, t_cmd **cmd, t_context *ctx)
{
	char	**args;
	char	*str_exp;
	t_token	*tokens;
	int32_t	res;

	res = expand(&str_exp, str, ctx);
	if (res != 0)
		return (res);
	res = tokenize(&args, str_exp);
	free_vct(str_exp);
	if (res != 0)
		return (res);
	res = lexer(&tokens, args);
	free_split(args);
	if (res != 0)
		return (res);
	res = build_cmds(tokens, cmd, ctx);
	vct_destroy(tokens);
	return (res);
}
