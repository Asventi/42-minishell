/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjarnac <pjarnac@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 15:32:57 by pjarnac           #+#    #+#             */
/*   Updated: 2024/11/22 20:55:58 by pjarnac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	ft_putchar_fd(char c, int fd)
{
	size_t	total;
	ssize_t	res;

	total = 0;
	while (total == 0)
	{
		res = write(fd, &c, 1);
		if (res == -1)
			return ;
		total += res;
	}
}
