/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nseon <nseon@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 12:33:43 by nseon             #+#    #+#             */
/*   Updated: 2025/03/21 09:21:05 by nseon            ###   ########.fr       */
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
	char	cmd_test[PATH_MAX];
	int32_t	i;

	i = -1;
	paths = ft_split(getenv("PATH"), ':');
	if (!paths)
		return (-1);
	while (paths[++i])
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

int	is_builtins(t_cmd *cmd)
{
	if (!ft_strcmp(cmd->path, "cd"))
		cd_cmd(cmd);
	else if (!ft_strcmp(cmd->path, "echo"))
		echo_cmd(cmd);
	else
		return (1);
	return (0);
}

int	exec_cmd(t_cmd *cmd)
{
	pid_t	id;
	int		status;
	int		pipefd[2];

	cmd->args = malloc(sizeof (t_cmd));
	cmd->args[0] = ft_strdup("lib/");
	cmd->nb_args = 2;
	if (!is_builtins(cmd))
		return (0);
	id = fork();
	if (id == -1)
		return (p_error("fork", 0, 0));
	if (!id)
	{
		if (check_op(cmd, pipefd))
			return (errno);
		if (execve(cmd->path, cmd->args, cmd->env) == -1)
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
