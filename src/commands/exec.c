/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nseon <nseon@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 12:33:43 by nseon             #+#    #+#             */
/*   Updated: 2025/03/10 16:35:06 by nseon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <libft.h>
#include <stdlib.h>

int	verif_rights(char *pathname)
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

int search_path(char *cmd)
{
	char	*path;
	path = getenv("PATH");
	ft_printf("%s\n", path);
}
