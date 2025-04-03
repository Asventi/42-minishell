/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nseon <nseon@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 09:40:00 by nseon             #+#    #+#             */
/*   Updated: 2025/03/27 09:47:12 by nseon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.h"
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>

#include "env.h"
#include "errors.h"
#include "redirect.h"
#include "shell/prompt.h"
#include "libft.h"
#include "unistd.h"
#include "utils.h"

extern int32_t	g_sig;

static int32_t	get_var(char **res, char **str)
{
	int32_t	i;

	*res = vct_create(sizeof (char), 0, DESTROY_ON_FAIL);
	if (!*res)
		return (-1);
	i = -1;
	while (ft_isalnum((*str)[++i]))
	{
		if (vct_add(res, *str + i) != 0)
			return (-1);
		if (ft_isdigit((*str)[0]) && ++i)
			break ;
	}
	if (**str == '?' && ++i)
		if (vct_add(res, *str) != 0)
			return (-1);
	(*str) += i;
	if (vct_add(res, &(char){0}) != 0)
		return (-1);
	return (0);
}

static void	expand_heredoc_quote(int32_t fd, char *envname, t_context *ctx)
{
	char	*envvar;

	envvar = ft_getenv(envname, ctx);
	if (envvar == NULL)
		return ;
	while (*envvar)
	{
		write(fd, envvar, 1);
		envvar++;
	}
}

static int32_t	write_to_doc(char *line, int32_t tmp_file,
					t_context *ctx, bool quoted)
{
	char	*envvar;

	while (*line)
	{
		if (quoted == 0 && *line == '$')
		{
			line++;
			if (get_var(&envvar, &line) == -1)
				return (FATAL);
			expand_heredoc_quote(tmp_file, envvar, ctx);
		}
		else
		{
			write(tmp_file, line, 1);
			line++;
		}
	}
	write(tmp_file, "\n", 1);
	return (0);
}

int32_t	heredoc(char *deli, t_context *ctx, bool quoted)
{
	char	*line;
	int32_t	tmp_file;

	tmp_file = create_temp_file();
	if (tmp_file == -1)
		return (-1);
	while (!g_sig)
	{
		line = readline(BROWN "> " RESET);
		if (line && ft_strcmp(line, deli) != 0 && !g_sig)
		{
			if (write_to_doc(line, tmp_file, ctx, quoted) == -1)
				return (FATAL);
		}
		else
		{
			if (!line && !g_sig)
				printf(HEREDOC_WARN, deli);
			free(line);
			break ;
		}
		free(line);
	}
	return (open_temp_file(&tmp_file));
}

//TODO: gestion sinaux heredoc
//TODO: expend les envar tout le temps
//TODO: ne pas expend si le dimiter est entre quotes
