/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rout.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nseon <nseon@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 09:36:45 by nseon             #+#    #+#             */
/*   Updated: 2025/03/27 09:50:14 by nseon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.h"
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>

int	rout(t_cmd *cmd)
{
	int	fd;

	fd = open(cmd->output.path, O_WRONLY | O_TRUNC);
	if (fd == -1)
		return (errno);
	dup2(fd, 1);
	return (0);
}
