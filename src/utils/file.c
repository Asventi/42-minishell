/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjarnac <pjarnac@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 19:09:42 by pjarnac           #+#    #+#             */
/*   Updated: 2025/03/20 19:09:42 by pjarnac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>

#include "utils.h"
#include "errors.h"
#include "libft.h"
#include "context.h"
#include "env.h"
#include "builtins.h"
#include "redirect.h"

int	search_path(char *cmd, char cmd_path[PATH_MAX], t_context *ctx)
{
	char	**paths;
	char	*pathenv;
	char	cmd_test[PATH_MAX];
	int32_t	i;

	i = -1;
	pathenv = ft_getenv("PATH", ctx);
	if (!pathenv)
		return (ft_strlcpy(cmd_path, cmd, PATH_MAX), 0);
	paths = ft_split(pathenv, ':');
	if (!paths)
		return (-1);
	while (paths[++i] && !is_builtins(cmd))
	{
		ft_strlcpy(cmd_test, paths[i], PATH_MAX);
		ft_strlcat(cmd_test, "/", PATH_MAX);
		ft_strlcat(cmd_test, cmd, PATH_MAX);
		if (!access(cmd_test, F_OK))
		{
			ft_strlcpy(cmd_path, cmd_test, PATH_MAX);
			return (free_split(paths), 0);
		}
	}
	ft_strlcpy(cmd_path, cmd, PATH_MAX);
	return (free_split(paths), 0);
}

int32_t	close_in_out(int32_t in, int32_t out)
{
	if (in != 0 && in != 1)
		if (close(in) == -1)
			p_error("input", 0, 0);
	if (out != 1 && out != 0)
		if (close(out) == -1)
			ft_fprintf(2, "Close error on output file: %d\n", out);
	return (0);
}

int32_t	create_temp_file(void)
{
	int32_t	tmp_file;

	unlink(TMP_HEREDOC);
	tmp_file = open(TMP_HEREDOC, O_RDWR | O_CREAT | O_EXCL, 0644);
	return (tmp_file);
}

int32_t	open_temp_file(int32_t *tmp_file)
{
	close(*tmp_file);
	*tmp_file = open(TMP_HEREDOC, O_RDONLY);
	if (*tmp_file == -1)
		return (-1);
	unlink(TMP_HEREDOC);
	return (*tmp_file);
}
