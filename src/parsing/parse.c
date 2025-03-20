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
#include <unistd.h>

#include "context.h"
#include "command.h"
#include "parsing.h"
#include "libft.h"
#include "utils.h"
#include "errors.h"

static int32_t	process_token(t_token *token, t_cmd *cmd)
{
	if (token->type == COMMAND)
	{
		if (search_path(token->txt, cmd->path) != 0)
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
	return (0);
}

static int32_t	build_cmds(t_token *tokens, t_cmd **cmd, t_context *ctx)
{
	const size_t	tk_size = vct_size(tokens);
	int32_t			i;
	int32_t			j;
	int32_t			res;

	*cmd = create_vector(sizeof (t_cmd));
	if (!*cmd)
		return (-1);
	j = -1;
	i = -1;
	while (++i < tk_size)
	{
		if (i == 0 || tokens[i].type == PIPE)
		{
			vct_allocate(cmd, 1);
			j++;
		}
		res = process_token(&tokens[i], *cmd + j);
		if (res != 0)
			return (res);
	}
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
	/* TODO: Free tokens allocated text, either using dedicated function or making a
	/ destroy vector function that takes a func ptr to delete.
	*/
	free_vct(tokens);
	if (res != 0)
		return (res);
	return (0);
}
