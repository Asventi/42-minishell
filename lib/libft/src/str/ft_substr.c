/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjarnac <pjarnac@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 16:24:40 by pjarnac           #+#    #+#             */
/*   Updated: 2024/11/12 17:09:16 by pjarnac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stddef.h>

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	slen;
	size_t	ressize;
	char	*res;
	size_t	i;

	if (!s)
		return (NULL);
	slen = ft_strlen(s);
	if (start >= slen)
		ressize = 0;
	else if (slen - start >= len)
		ressize = len;
	else
		ressize = slen - start;
	res = ft_calloc(ressize + 1, sizeof (char));
	if (!res)
		return (NULL);
	i = 0;
	while (i < ressize)
	{
		res[i] = s[start + i];
		i++;
	}
	return (res);
}
