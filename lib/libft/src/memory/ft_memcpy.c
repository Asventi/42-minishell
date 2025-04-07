/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjarnac <pjarnac@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 16:48:41 by pjarnac           #+#    #+#             */
/*   Updated: 2024/11/12 16:02:31 by pjarnac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

void	*ft_memcpy(void	*dest, const void *src, size_t n)
{
	while (n)
	{
		((unsigned char *)dest)[n - 1] = ((const unsigned char *)src)[n - 1];
		n--;
	}
	return (dest);
}
