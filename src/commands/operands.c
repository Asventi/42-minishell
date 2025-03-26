/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nseon <nseon@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 08:40:45 by nseon             #+#    #+#             */
/*   Updated: 2025/03/17 13:44:10 by nseon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <command.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <limits.h>
#include "redirect.h"
#include "libft.h"
#include "shell/prompt.h"

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

int	heredoc(t_cmd *cmd, int pipefd[2])
{
	char	buf[BUF_SIZE];
	char	input[BUF_SIZE];
	int		nb_read;

	nb_read = 1;
	ft_bzero(input, BUF_SIZE);
	while (nb_read)
	{
		write (1, BROWN "> " RESET, ft_strlen(BROWN "> " RESET));
		ft_bzero(buf, BUF_SIZE);
		nb_read = (int32_t)read(0, buf, BUF_SIZE);
		if (nb_read == -1)
			return (errno);
		if (nb_read - 1 == (int32_t) ft_strlen(cmd->input.path)
			&& !ft_strncmp(buf, cmd->input.path, nb_read - 1))
			break ;
		if (nb_read)
			ft_strlcat(input, buf, BUF_SIZE);
	}
	if (pipe(pipefd) == -1)
		return (errno);
	write(pipefd[1], input, ft_strlen(input));
	close(pipefd[1]);
	dup2(pipefd[0], 0);
	return (0);
}

int	check_op(t_cmd *cmd, int pipefd[2])
{
	if (cmd->output.op == ROUT)
		if (rout(cmd))
			return (-1);
	if (cmd->output.op == ROUTAPP)
		if (routapp(cmd))
			return (-1);
	if (cmd->input.op == RIN)
		if (rin(cmd))
			return (-1);
	if (cmd->input.op == HEREDOC)
		if (heredoc(cmd, pipefd))
			return (-1);
	return (0);
}
