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

#include "redirect.h"
#include "shell/prompt.h"
#include "libft.h"
#include "unistd.h"

extern int32_t	g_sig;

static int32_t	create_temp_file(void)
{
	int32_t	tmp_file;

	unlink(TMP_HEREDOC);
	tmp_file = open(TMP_HEREDOC, O_RDWR | O_CREAT | O_EXCL, 0644);
	return (tmp_file);
}

static int32_t	open_temp_file(int32_t *tmp_file)
{
	close(*tmp_file);
	*tmp_file = open(TMP_HEREDOC, O_RDONLY);
	if (*tmp_file == -1)
		return (-1);
	unlink(TMP_HEREDOC);
	return (0);
}

static void	write_to_doc(char *line, int32_t tmp_file)
{
	write(tmp_file, line, ft_strlen(line));
	write(tmp_file, "\n", 1);
}

int32_t	heredoc(t_cmd *cmd)
{
	char	*line;
	int32_t	tmp_file;

	tmp_file = create_temp_file();
	if (tmp_file == -1)
		return (-1);
	while (!g_sig)
	{
		line = readline(BROWN "> " RESET);
		if (line && ft_strcmp(line, cmd->input.path) != 0 && !g_sig)
			write_to_doc(line, tmp_file);
		else
		{
			if (!line && !g_sig)
				printf(HEREDOC_WARN, cmd->input.path);
			free(line);
			break ;
		}
		free(line);
	}
	if (open_temp_file(&tmp_file) == -1)
		return (-1);
	if (dup2(tmp_file, 0) == -1)
		return (-1);
	return (0);
}
