/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nseon <nseon@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 10:05:50 by nseon             #+#    #+#             */
/*   Updated: 2025/03/27 15:49:02 by nseon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.h"
#include <unistd.h>
#include "context.h"
#include "libft.h"
#include "builtins.h"
#include <fcntl.h>

int	pipe_init(int *pipefd, int out, int in)
{
	if (pipe(pipefd) == -1)
		return (-1);
	if (dup2(pipefd[out], 1) == -1)
		return (-1);
	if (dup2(pipefd[in], 0) == -1)
		return (-1);
	return (0);
}

int	child_builtins(t_cmd *cmd, t_context *ctx, int id)
{
	if (id == 0)
	{
		if (launch_builtins(cmd, ctx) == -1)
			return (CHLD_ERR);
		else
			return (CHLD_END);
	}
}

int	launch_all_cmd(t_cmd *cmd, t_context *ctx, int fd, int *pipefds)
{
	int	id;
	int	i;
	int	res;

	i = -1;
	while (++i < vct_size(cmd))
	{
		cmd += i;
		if (i == vct_size(cmd) - 1)
			if (dup2(fd, 1) == -1)
				return (-1);
		if (is_builtins(cmd->path))
		{
			id = fork();
			if (id == -1)
				return (CHLD_ERR);
			res = child_builtins(cmd, ctx, id);
			if (id == 0 && (res == CHLD_END || res == CHLD_ERR))
				return (res);
		}
		else
			if (exec_cmd(cmd, ctx))
				return (-1);
	}
	return (0);
}

int	pipex(t_cmd *cmd, t_context *ctx)
{
	int	*pipefds;
	int	fd;
	int	res;

	fd = open(ctx->tty, O_RDWR);
	if (fd == -1)
		return (-1);
	pipefds = vct_create(2 * vct_size(cmd) - 1 * sizeof(int), 0, 0);
	if (!pipefds)
		return (-1);
	res = launch_all_cmd(cmd, ctx, fd, pipefds);
	if (dup2(fd, 0) == -1)
		return (-1);
	return (res);
}
