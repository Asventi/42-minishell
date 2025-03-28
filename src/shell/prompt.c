/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nseon <nseon@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 13:41:23 by pjarnac           #+#    #+#             */
/*   Updated: 2025/03/27 11:18:34 by nseon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <stdio.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "command.h"
#include "context.h"
#include "libft.h"
#include "shell/prompt.h"

#include <stdlib.h>

#include "parsing.h"

static char	*get_prompt(char str[PATH_MAX + 32], t_context *ctx)
{
	str[0] = 0;
	ft_strlcat(str, "\n" CYAN, PATH_MAX + 32);
	ft_strlcat(str, ctx->path, PATH_MAX + 32);
	ft_strlcat(str, RESET, PATH_MAX + 32);
	if (ctx->last_code != 0)
		ft_strlcat(str, RED_PROMPT, PATH_MAX + 32);
	else
		ft_strlcat(str, GREEN_PROMPT, PATH_MAX + 32);
	return (str);
}

static int32_t	process_command(char *line, t_context *ctx)
{
	t_cmd	*cmd;
	int32_t	res;

	res = parse(line, &cmd, ctx);
	if (res != 0)
		return (res);
	if (vct_size(cmd) > 1)
		res = pipex(cmd, ctx);
	else
		res = exec_cmd(cmd, ctx);
	vct_destroy(cmd);
	return (res);
}

int	prompt(t_context *ctx)
{
	char	ptext[PATH_MAX + 32];
	char	*line;
	int32_t	res;

	while (1)
	{
		getcwd(ctx->path, PATH_MAX);
		line = readline(get_prompt(ptext, ctx));
		if (!line)
			return (printf("exit\n"), 0);
		if (*line)
			add_history(line);
		else
			continue ;
		res = process_command(line, ctx);
		free(line);
		if (res == -1 || res == CHLD_ERR || res == CHLD_END)
			return (res);
	}
}
