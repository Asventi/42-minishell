/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nseon <nseon@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 13:41:23 by pjarnac           #+#    #+#             */
/*   Updated: 2025/04/07 15:14:04 by nseon            ###   ########.fr       */
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
#include "errors.h"
#include <stdlib.h>
#include <signal.h>

#include "parsing.h"
#include "signals.h"

extern int32_t	g_sig;

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

int32_t	process_command(char *line, t_context *ctx)
{
	t_cmd	*cmd;
	int32_t	res;

	res = parse(line, &cmd, ctx);
	if (res != 0)
	{
		ctx->last_code = 2;
		return (res);
	}
	res = exec_line(cmd, ctx);
	vct_destroy(cmd);
	return (res);
}

static void	set_lastcode_sig(t_context *ctx)
{
	if (g_sig == SIGINT)
		ctx->last_code = 130;
	if (g_sig == SIGQUIT)
		ctx->last_code = 131;
}

int	prompt(t_context *ctx)
{
	char	ptext[PATH_MAX + 32];
	char	*line;
	int32_t	res;

	getcwd(ctx->path, PATH_MAX);
	while (1)
	{
		init_signals_main();
		g_sig = 0;
		res = 0;
		line = readline(get_prompt(ptext, ctx));
		if (!line)
			return (printf("exit\n"), 0);
		if (*line)
		{
			add_history(line);
			res = process_command(line, ctx);
		}
		free(line);
		if (res == -1 || res == EXIT || res == CHLD_END)
			return (res);
		set_lastcode_sig(ctx);
	}
}
