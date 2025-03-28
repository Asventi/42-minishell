/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nseon <nseon@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 12:33:43 by nseon             #+#    #+#             */
/*   Updated: 2025/03/27 11:22:56 by nseon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <libft.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>
#include <stdint.h>
#include <sys/wait.h>
#include "command.h"
#include "redirect.h"
#include "errors.h"
#include "builtins.h"
#include "context.h"

int32_t	exec_builtin(t_cmd *cmd, t_context *ctx, int32_t fdin, int32_t fdout)
{
	int	id;

	if (fdin != 0 || fdout != 1)
	{
		id = fork();
		if (id == -1)
			return (-1);
		if (!id)
		{
			if (dup2(fdin, 0) == -1)
				return (CHLD_ERR);
			if (dup2(fdout, 1) == -1)
				return (CHLD_ERR);
			if (check_op(cmd) == -1 || launch_builtins(cmd, ctx) == -1)
				return (CHLD_ERR);
			return (CHLD_END);
		}
	}
	else
	{
		if (check_op(cmd) == - 1)
			return (-1);
		return (launch_builtins(cmd, ctx));
	}
	if (fdout != 1)
		close(fdout);
	if (fdin != 0)
		close (fdin);
	return (0);
}

int32_t	exec_cmd(t_cmd *cmd, t_context *ctx, int32_t fdin, int32_t fdout)
{
	int	id;

	id = fork();
	if (id == -1)
		return (-1);
	if (!id)
	{
		if (dup2(fdin, 0) == -1)
			return (CHLD_ERR);
		if (dup2(fdout, 1) == -1)
			return (CHLD_ERR);
		// TODO: Deplacer les heredoc dnas le parsing
		if (check_op(cmd) == -1
			|| execve(cmd->path, cmd->args, ctx->env) == -1)
			return (CHLD_ERR - (errno == ENOENT));
	}
	if (fdout != 1)
		close(fdout);
	if (fdin != 0)
		close (fdin);
	return (0);
}

int32_t	choose_exec(t_cmd *cmd, t_context *ctx, int32_t fdin, int32_t fdout)
{
	if (is_builtins(cmd->path))
		return (exec_builtin(cmd, ctx, fdin, fdout));
	if (ft_strlen(cmd->path) != 0 && access(cmd->path, F_OK) != 0)
		return (p_error(cmd->path, 0, "command not found"), 1);
	return (exec_cmd(cmd, ctx, fdin, fdout));
}

int32_t	exec_line(t_cmd *cmd, t_context *ctx)
{
	int32_t	pipefd[2];
	int32_t	old_pipe;
	int32_t	i;
	int32_t	res;

	i = -1;
	pipefd[0] = 0;
	pipefd[1] = 1;
	while (++i < (int32_t)vct_size(cmd))
	{
		old_pipe = pipefd[0];
		if ((int32_t)vct_size(cmd) > 1 && i < (int32_t)vct_size(cmd) - 1)
			if  (pipe(pipefd) == -1)
				return (-1);
		if (i == (int32_t)vct_size(cmd) - 1)
			res = choose_exec(&cmd[i], ctx, old_pipe, 1);
		else
			res = choose_exec(&cmd[i], ctx, old_pipe, pipefd[1]);
		if (res == -1 || res == CHLD_ERR || res == CHLD_END)
			return (res);
	}
	while (wait(&ctx->status) != -1)
	{
		ctx->last_code = WEXITSTATUS(ctx->status);
		if (ctx->last_code == CHLD_ERR)
			return (-1);
	}
	return (0);
}
