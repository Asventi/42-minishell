/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nseon <nseon@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 12:33:43 by nseon             #+#    #+#             */
/*   Updated: 2025/03/20 16:26:07 by nseon            ###   ########.fr       */
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

int	verif_rights(char *pathname)
{
	int	rights;

	rights = 0;
	if (access(pathname, F_OK) == -1)
		return (-1);
	if (!access(pathname, R_OK))
		rights += 04;
	if (!access(pathname, W_OK))
		rights += 02;
	if (!access(pathname, X_OK))
		rights += 01;
	return (rights);
}

int	search_path(char *cmd, char cmd_path[PATH_MAX])
{
	char	**paths;
	int32_t	i;

	i = -1;
	paths = ft_split(getenv("PATH"), ':');
	if (!paths)
		return (errno);
	while (paths[++i])
	{
		ft_strlcpy(cmd_path, paths[i], PATH_MAX);
		ft_strlcat(cmd_path, "/", PATH_MAX);
		ft_strlcat(cmd_path, cmd, PATH_MAX);
		if (!access(cmd_path, F_OK))
		{
			free_split(paths);
			return (0);
		}
	}
	free_split(paths);
	ft_bzero(cmd_path, PATH_MAX);
	return (ENOENT);
}

int	is_builtins(t_cmd *cmd)
{
	if (cmd->path == "cd")
		cd_cmd(cmd);
}

int	exec_cmd(t_cmd *cmd)
{
	pid_t	id;
	int		status;
	int		pipefd[2];

	id = fork();
	if (id == -1)
		return (p_error("fork"));
	if (!id)
	{
		if (check_op(cmd, pipefd))
			return (errno);
		if (execve(cmd->path, cmd->args, cmd->env) == -1)
			p_errorexit(cmd->path);
	}
	if (id)
	{
		if (wait(&status) == -1)
			return (errno);
		return (WEXITSTATUS(status));
	}
	return (0);
}
