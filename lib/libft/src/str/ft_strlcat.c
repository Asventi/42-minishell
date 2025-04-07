/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjarnac <pjarnac@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 18:47:15 by pjarnac           #+#    #+#             */
/*   Updated: 2024/11/20 11:08:29 by pjarnac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	j;
	size_t	dest_size;

	if (size == 0)
		return (ft_strlen(src));
	i = 0;
	while (dst[i])
	{
		if (i == size)
			return (size + ft_strlen(src));
		i++;
	}
	dest_size = i;
	j = i;
	while (src[i - j] && i < size - 1)
	{
		dst[i] = src[i - j];
		i++;
	}
	dst[i] = 0;
	return (ft_strlen(src) + dest_size);
}
