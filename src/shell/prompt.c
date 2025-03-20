/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjarnac <pjarnac@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 13:41:23 by pjarnac           #+#    #+#             */
/*   Updated: 2025/03/06 13:41:23 by pjarnac          ###   ########.fr       */
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

int	prompt(t_context *ctx)
{
	char	ptext[PROMPT_MAX];
	char	*line;
	t_cmd	cmd;

	ft_bzero(&cmd, sizeof (t_cmd));
	getcwd(ctx->path, PATH_MAX);
	while (1)
	{
		errno = 0;
		line = readline(get_prompt(ptext, ctx));
		if (!line)
			return (printf("exit\n"), 0);
		if (*line)
			add_history(line);
		parse(line, &cmd, ctx);
		free(line);
	}
	return (0);
}
