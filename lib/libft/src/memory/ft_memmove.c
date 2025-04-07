/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjarnac <pjarnac@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 17:34:37 by pjarnac           #+#    #+#             */
/*   Updated: 2024/11/12 16:11:54 by pjarnac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*udest;
	unsigned char	*usrc;
	int				i;

	udest = (unsigned char *)dest;
	usrc = (unsigned char *)src;
	if (dest < src)
	{
		i = -1;
		while (++i < (int)n)
			udest[i] = usrc[i];
	}
	else
	{
		while (n)
		{
			udest[n - 1] = usrc[n - 1];
			n--;
		}
	}
	return (dest);
}
