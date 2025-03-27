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
#include <stdio.h>
#include <sys/wait.h>
#include "command.h"
#include "redirect.h"
#include "errors.h"
#include "builtins.h"
#include "context.h"
#include "env.h"

int	exec_cmd(t_cmd *cmd, t_context *ctx)
{
	pid_t	id;
	int		status;

	if (is_builtins(cmd->path))
		return (launch_builtins(cmd, ctx));
	if (ft_strlen(cmd->path) > 0 && access(cmd->path, F_OK) != 0)
	{
		ctx->last_code = 127;
		return (p_error(cmd->path, 0, "command not found"), 1);
	}
	id = fork();
	if (id == -1)
		return (p_error("fork", 0, 0));
	if (!id)
		if (check_op(cmd) == -1
			|| execve(cmd->path, cmd->args, ctx->env) == -1)
			return (CHLD_ERR - (errno == ENOENT));
	if (wait(&status) == -1)
		return (-1);
	ctx->last_code = WEXITSTATUS(status);
	if (ctx->last_code == CHLD_ERR)
		return (-1);
	return (0);
}
