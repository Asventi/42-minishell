/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rin.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nseon <nseon@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 09:39:22 by nseon             #+#    #+#             */
/*   Updated: 2025/03/27 10:50:24 by nseon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.h"
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>

int	rin(t_cmd *cmd)
{
	int	fd;

	fd = open(cmd->input.path, O_RDONLY);
	if (fd == -1)
		return (errno);
	if (dup2(fd, 0))
		return (-1);
	return (0);
}
