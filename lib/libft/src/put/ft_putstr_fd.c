/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjarnac <pjarnac@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 15:44:07 by pjarnac           #+#    #+#             */
/*   Updated: 2024/11/22 21:17:02 by pjarnac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>

void	ft_putstr_fd(char *s, int fd)
{
	size_t	count;
	ssize_t	res;

	count = ft_strlen(s);
	while (count > 0)
	{
		res = write(fd, s, count);
		if (res < 0)
			return ;
		s += res;
		count -= res;
	}
}
