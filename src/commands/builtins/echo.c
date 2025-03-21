/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nseon <nseon@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 16:40:08 by nseon             #+#    #+#             */
/*   Updated: 2025/03/21 11:08:34 by nseon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <command.h>
#include "libft.h"
#include <stdio.h>

int	echo_cmd(t_cmd *cmd)
{
	int		i;
	int		check;
	char	*str;

	i = 0;
	check = 0;
	if (!ft_strcmp(cmd->args[i], "-n"))
		check = ++i;
	while (cmd->args[i])
	{
		if (i != check)
			printf(" ");
		printf("%s\n", cmd->args[i]);
		i++;
	}
	if (!check)
		printf("\n");
	return (0);
}
