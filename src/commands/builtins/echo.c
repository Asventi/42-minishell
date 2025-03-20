/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nseon <nseon@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 16:40:08 by nseon             #+#    #+#             */
/*   Updated: 2025/03/20 17:10:41 by nseon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <command.h>
#include "libft.h"

int	echo_cmd(t_cmd *cmd)
{
	int		i;
	int		check;
	char	*str;

	i = 0;
	check = 0;
	if (cmd->args[i] == "-n")
		check = ++i;
	while (cmd->args[i])
	{
		if (i != check)
			write(1, " ", 1);
		write(1, cmd->args[i], ft_strlen(cmd->args[i]));
		i++;
	}
	if (!check)
		write(1, "\n", 1);
	return (0);
}
