/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nseon <nseon@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 10:05:50 by nseon             #+#    #+#             */
/*   Updated: 2025/03/27 15:01:17 by nseon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.h"
#include <unistd.h>
#include "context.h"
#include "libft.h"
#include "builtins.h"
#include <fcntl.h>

int	launch_all_cmd(t_cmd *cmd, t_context *ctx, int fd)
{
	int	id;
	int	i;

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
			if (id == 0)
			{
				if (launch_builtins(cmd, ctx) == -1)
					return (CHLD_ERR);
				else
					return (CHLD_END);
			}
		}
		else
			if (exec_cmd(cmd, ctx))
				return (-1);
	}
	if (dup2(fd, 0) == -1)
				return (-1);
	return (0);
}

int	pipex(t_cmd *cmd, t_context *ctx)
{
	int	pipefd[2];
	int	fd;

	fd = open(ctx->tty, O_RDWR);
	if (fd == -1)
		return (-1);
	if (pipe(pipefd) == -1)
		return (-1);
	if (dup2(pipefd[1], 1) == -1)
		return (-1);
	if (dup2(pipefd[0], 0) == -1)
		return (-1);
	return (launch_all_cmd(cmd, ctx, fd));
}
