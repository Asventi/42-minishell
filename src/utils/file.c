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

int32_t	check_file_create(char *str)
{
	int32_t	res;

	res = open(str, O_CREAT, 0644);
	if (res == -1)
		return (p_error(str, 0, 0));
	close(res);
	return (0);
}

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

int32_t	reset_stds(t_context *ctx)
{
	int32_t	fd;

	fd = open(ctx->tty, O_RDWR);
	if (fd == -1)
		return (-1);
	if (dup2(fd, 1) == -1)
		return (-1);
	if (dup2(fd, 0) == -1)
		return (-1);
	return (0);
}

int32_t	close_pipe(int32_t pipefd[2])
{
	if (pipefd[0] != 0)
		close(pipefd[0]);
	if (pipefd[1] != 1)
		close(pipefd[1]);
	return (0);
}

int32_t	close_in_out(int32_t in, int32_t out)
{
	if (in != 0)
		if (close(in) == -1)
			p_error("input", 0, 0);
	if (out != 1)
		if (close(out) == -1)
			ft_fprintf(2, "Close error on output file: %d\n", out);
	return (0);
}
