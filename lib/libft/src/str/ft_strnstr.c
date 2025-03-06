/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjarnac <pjarnac@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 19:49:35 by pjarnac           #+#    #+#             */
/*   Updated: 2024/11/12 16:35:23 by pjarnac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stddef.h>

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	little_s;

	i = 0;
	little_s = ft_strlen(little);
	if (little_s == 0)
		return ((char *)big);
	while (big[i] && i < len)
	{
		if (little_s <= len - i)
		{
			if (!ft_strncmp(big + i, little, little_s))
				return ((char *)(big + i));
		}
		i++;
	}
	return (NULL);
}
