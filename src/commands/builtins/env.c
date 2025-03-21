/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nseon <nseon@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 10:34:23 by nseon             #+#    #+#             */
/*   Updated: 2025/03/21 11:29:15 by nseon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.h"
#include "libft.h"
#include <stdio.h>

int	env_cmd(t_cmd *cmd)
{
	int	i;

	i = 0;
	while (cmd->env[i])
	{
		printf("%s\n", cmd->env[i]);
		i++;
	}
	return (0);
}
