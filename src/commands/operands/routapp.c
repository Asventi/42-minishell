/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routapp.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nseon <nseon@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 09:38:28 by nseon             #+#    #+#             */
/*   Updated: 2025/03/27 10:55:13 by nseon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.h"
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>

int	routapp(t_cmd *cmd)
{
	if (dup2(cmd->output.fd, 1) == -1)
		return (close(cmd->output.fd), -1);
	return (0);
}
