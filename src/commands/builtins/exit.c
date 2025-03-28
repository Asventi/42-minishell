/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nseon <nseon@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 09:44:58 by nseon             #+#    #+#             */
/*   Updated: 2025/03/26 11:07:51 by nseon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

int	exit_cmd(void)
{
	printf("exit\n");
	return (-1);
}

//TODO: Exit avec des arguments, le code de sortie est celui specifie si yen a un, si plusieurs et chiffre en derniere on exit mais avec 2
// sinon si lettre en dernier exit pas et message derreure
