/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nseon <nseon@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 08:40:45 by nseon             #+#    #+#             */
/*   Updated: 2025/03/12 11:28:33 by nseon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <command.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

void check_op(t_cmd *cmd)
{
	int fd;

	if (cmd->output.op == ROUT)
	{
		fd = open(cmd->output.path, O_WRONLY | O_TRUNC);
		dup2(fd, 1);
	}
	if (cmd->output.op == ROUTAPP)
	{
		fd = open(cmd->output.path, O_WRONLY | O_APPEND);
		dup2(fd, 1);
	}
}
