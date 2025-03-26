/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nseon <nseon@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 12:33:43 by nseon             #+#    #+#             */
/*   Updated: 2025/03/26 11:08:54 by nseon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <libft.h>
#include <stdlib.h>
#include <errno.h>
#include <stdint.h>
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
	char	cmd_test[PATH_MAX];
	int32_t	i;

	i = -1;
	paths = ft_split(ft_getenv("PATH", ctx), ':');
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
			free_split(paths);
			return (0);
		}
	}
	free_split(paths);
	ft_strlcpy(cmd_path, cmd, PATH_MAX);
	return (0);
}

int	launch_builtins(t_cmd *cmd, t_context *ctx)
{
	int32_t	res;

	res = 0;
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
	ctx->last_code = res;
	return (res);
}

int	exec_cmd(t_cmd *cmd, t_context *ctx)
{
	pid_t	id;
	int		status;
	int		pipefd[2];

	if (is_builtins(cmd->path))
		return (launch_builtins(cmd, ctx));
	if (access(cmd->path, F_OK) != 0)
	{
		ctx->last_code = 127;
		return (p_error(cmd->path, 0, "command not found"), 1);
	}
	id = fork();
	if (id == -1)
		return (p_error("fork", 0, 0));
	if (!id)
		if (check_op(cmd, pipefd) == -1
			|| execve(cmd->path, cmd->args, ctx->env) == -1)
			return (CHLD_ERR);
	if (wait(&status) == -1)
		return (-1);
	ctx->last_code = WEXITSTATUS(status);
	if (ctx->last_code == CHLD_ERR)
		return (-1);
	return (WEXITSTATUS(status));
}
