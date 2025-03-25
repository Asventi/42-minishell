/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nseon <nseon@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 12:33:43 by nseon             #+#    #+#             */
/*   Updated: 2025/03/25 10:33:28 by nseon            ###   ########.fr       */
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

int	is_builtins(char *cmd)
{
	if (!ft_strcmp(cmd, "cd"))
		return (0);
	else if (!ft_strcmp(cmd, "echo"))
		return (0);
	else if (!ft_strcmp(cmd, "pwd"))
		return (0);
	else if (!ft_strcmp(cmd, "exit"))
		return (0);
	else if (!ft_strcmp(cmd, "env"))
		return (0);
	else if (!ft_strcmp(cmd, "export"))
		return (0);
	else if (!ft_strcmp(cmd, "unset"))
		return (0);
	return (1);
}

int	search_path(char *cmd, char cmd_path[PATH_MAX])
{
	char	**paths;
	char	cmd_test[PATH_MAX];
	int32_t	i;

	i = -1;
	paths = ft_split(getenv("PATH"), ':');
	if (!paths)
		return (-1);
	while (paths[++i] && is_builtins(cmd))
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
	if (!ft_strcmp(cmd->path, "cd"))
		cd_cmd(cmd);
	else if (!ft_strcmp(cmd->path, "echo"))
		echo_cmd(cmd);
	else if (!ft_strcmp(cmd->path, "pwd"))
		pwd_cmd(cmd);
	else if (!ft_strcmp(cmd->path, "exit"))
		exit_cmd();
	else if (!ft_strcmp(cmd->path, "env"))
		env_cmd(ctx);
	else if (!ft_strcmp(cmd->path, "export"))
		export_cmd(cmd, ctx);
	else if (!ft_strcmp(cmd->path, "unset"))
		unset_cmd(cmd, ctx);
	else
		return (1);
	return (0);
}

int	exec_cmd(t_cmd *cmd, t_context *ctx)
{
	pid_t	id;
	int		status;
	int		pipefd[2];

	if (!launch_builtins(cmd, ctx))
		return (0);
	id = fork();
	if (id == -1)
		return (p_error("fork", 0, 0));
	if (!id)
	{
		if (check_op(cmd, pipefd))
			return (errno);
		if (execve(cmd->path, cmd->args, ctx->env) == -1)
			p_errorexit(cmd->path, 0, 0);
	}
	if (id)
	{
		if (wait(&status) == -1)
			return (errno);
		return (WEXITSTATUS(status));
	}
	return (0);
}
