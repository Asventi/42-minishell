/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nseon <nseon@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 12:33:43 by nseon             #+#    #+#             */
/*   Updated: 2025/03/27 10:49:43 by nseon            ###   ########.fr       */
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
		res = pwd_cmd(cmd);
	else if (!ft_strcmp(cmd->path, "exit"))
		res = exit_cmd();
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

	ctx->last_code = choose_builtins(cmd, ctx);
	fd = open(ctx->tty, O_RDWR);
	if (dup2(fd, 1) == -1)
		return (-1);
	if (dup2(fd, 0) == -1)
		return (-1);
	return (ctx->last_code);
}

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
			return (CHLD_ERR);
	if (wait(&status) == -1)
		return (-1);
	ctx->last_code = WEXITSTATUS(status);
	if (ctx->last_code == CHLD_ERR)
		return (-1);
	return (WEXITSTATUS(status));
}
