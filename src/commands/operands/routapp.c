/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routapp.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nseon <nseon@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 09:38:28 by nseon             #+#    #+#             */
/*   Updated: 2025/03/27 10:50:48 by nseon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.h"
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>

int	routapp(t_cmd *cmd)
{
	int	fd;

	fd = open(cmd->output.path, O_WRONLY | O_APPEND);
	if (fd == -1)
		return (errno);
	if (dup2(fd, 1))
		return (-1);
	return (0);
}
