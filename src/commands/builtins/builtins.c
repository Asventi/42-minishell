/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nseon <nseon@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 11:20:21 by nseon             #+#    #+#             */
/*   Updated: 2025/04/07 15:07:36 by nseon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.h"
#include "context.h"
#include "fcntl.h"
#include "builtins.h"
#include <unistd.h>
#include "libft.h"
#include "redirect.h"
#include "errors.h"

int	is_builtins(char *cmd)
{
	if (!ft_strcmp(cmd, "cd"))
		return (1);
	if (!ft_strcmp(cmd, "echo"))
		return (1);
	if (!ft_strcmp(cmd, "pwd"))
		return (1);
	if (!ft_strcmp(cmd, "exit"))
		return (1);
	if (!ft_strcmp(cmd, "env"))
		return (1);
	if (!ft_strcmp(cmd, "export"))
		return (1);
	if (!ft_strcmp(cmd, "unset"))
		return (1);
	return (0);
}

int	choose_builtins(t_cmd *cmd, t_context *ctx)
{
	int32_t	res;

	res = 0;
	if (check_op(cmd) == -1)
		return (-1);
	if (!ft_strcmp(cmd->path, "cd"))
		res = cd_cmd(cmd, ctx);
	else if (!ft_strcmp(cmd->path, "echo"))
		res = echo_cmd(cmd);
	else if (!ft_strcmp(cmd->path, "pwd"))
		res = pwd_cmd(ctx);
	else if (!ft_strcmp(cmd->path, "exit"))
		res = exit_cmd(cmd, ctx);
	else if (!ft_strcmp(cmd->path, "env"))
		res = env_cmd(ctx);
	else if (!ft_strcmp(cmd->path, "export"))
		res = export_cmd(cmd, ctx);
	else if (!ft_strcmp(cmd->path, "unset"))
		res = unset_cmd(cmd, ctx);
	return (res);
}

int	launch_builtins(t_cmd *cmd, t_context *ctx)
{
	int	fd;
	int	res;

	res = choose_builtins(cmd, ctx);
	if (cmd->input.op != NONE)
		close(cmd->input.fd);
	if (cmd->output.op != NONE)
		close(cmd->output.fd);
	fd = open(ctx->tty, O_RDWR);
	if (fd == -1)
		return (-1);
	if (dup2(fd, 1) == -1)
		return (close(fd), -1);
	if (dup2(fd, 0) == -1)
		return (close(fd), -1);
	close(fd);
	if (res == EXIT)
		return (EXIT);
	ctx->last_code = res;
	return (ctx->last_code);
}
