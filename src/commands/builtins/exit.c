/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nseon <nseon@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 09:44:58 by nseon             #+#    #+#             */
/*   Updated: 2025/03/21 11:28:43 by nseon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <command.h>
#include <stdlib.h>
#include <stdio.h>

void	exit_cmd(void)
{
	printf("exit\n");
	exit(EXIT_SUCCESS);
}
