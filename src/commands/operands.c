/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nseon <nseon@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 08:40:45 by nseon             #+#    #+#             */
/*   Updated: 2025/03/12 17:38:09 by nseon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <command.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>

int	rout(t_cmd *cmd)
{
	int	fd;

	fd = open(cmd->output.path, O_WRONLY | O_TRUNC);
	if (fd == -1)
		return (errno);
	dup2(fd, 1);
	return (0);
}

int	routapp(t_cmd *cmd)
{
	int	fd;

	fd = open(cmd->output.path, O_WRONLY | O_APPEND);
	if (fd == -1)
		return (errno);
	dup2(fd, 1);
	return (0);
}

int	rin(t_cmd *cmd)
{
	int	fd;

	fd = open(cmd->input.path, O_RDONLY);
	if (fd == -1)
		return (errno);
	dup2(fd, 0);
	return (0);
}

int	heredoc(t_cmd *cmd)
{
	int		pipefd[2];
	pid_t	id;

	if (pipe(pipefd) == -1)
		return (errno);
	id = fork();
}

int	check_op(t_cmd *cmd)
{
	if (cmd->output.op == ROUT)
		if (rout(cmd))
			return (errno);
	if (cmd->output.op == ROUTAPP)
		if (routapp(cmd))
			return (errno);
	if (cmd->input.op == RIN)
		if (rin(cmd))
			return (errno);
	if (cmd->input.op == HEREDOC)
		if (heredoc(cmd))
			return (errno);
	return (0);
}
