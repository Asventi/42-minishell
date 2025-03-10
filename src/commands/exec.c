/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nseon <nseon@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 12:33:43 by nseon             #+#    #+#             */
/*   Updated: 2025/03/10 16:25:45 by nseon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <libft.h>

int	verif_cmd(char *pathname)
{
	int rights;

	rights = 0;
	if (access(pathname, F_OK) == -1)
		return (-1);
	if (!access(pathname, R_OK))
		rights += 1;
	if (!access(pathname, W_OK))
		rights += 2;
	if (!access(pathname, X_OK))
		rights += 4;
	return (rights);
}

