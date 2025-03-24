/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nseon <nseon@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 16:40:08 by nseon             #+#    #+#             */
/*   Updated: 2025/03/21 14:26:13 by nseon            ###   ########.fr       */
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
	int		nb_words;

	i = 1;
	check = 0;
	nb_words = 0;
	if (!ft_strcmp(cmd->args[i], "-n"))
		check = ++i;
	while (cmd->args[i])
	{
		if (nb_words)
			printf(" ");
		printf("%s", cmd->args[i]);
		nb_words++;
		i++;
	}
	if (!check)
		printf("\n");
	return (0);
}
