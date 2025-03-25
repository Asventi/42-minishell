/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nseon <nseon@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 13:41:23 by pjarnac           #+#    #+#             */
/*   Updated: 2025/03/21 11:09:48 by nseon            ###   ########.fr       */
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

static char	*get_prompt(char str[PROMPT_MAX], t_context *ctx)
{
	str[0] = 0;
	ft_strlcat(str, "\n" CYAN, PROMPT_MAX);
	ft_strlcat(str, ctx->path, PROMPT_MAX);
	if (ctx->last_code != 0)
		ft_strlcat(str, RED_PROMPT, PROMPT_MAX);
	else
		ft_strlcat(str, GREEN_PROMPT, PROMPT_MAX);
	return (str);
}

static int32_t	process_command(char *line, t_context *ctx)
{
	t_cmd	*cmd;
	int32_t	res;

	res = parse(line, &cmd, ctx);
	if (res == 0)
	{
		exec_cmd(cmd, ctx);
		vct_destroy(cmd);
	}
	return (res);
}

int	prompt(t_context *ctx)
{
	char	ptext[PROMPT_MAX];
	char	*line;

	while (1)
	{
		getcwd(ctx->path, PATH_MAX);
		errno = 0;
		line = readline(get_prompt(ptext, ctx));
		if (!line)
			return (printf("exit\n"), 0);
		if (*line)
			add_history(line);
		else
			continue ;
		if (process_command(line, ctx) == -1)
			return (free(line), -1);
		free(line);
	}
}
