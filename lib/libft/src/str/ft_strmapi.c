/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjarnac <pjarnac@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 14:55:59 by pjarnac           #+#    #+#             */
/*   Updated: 2024/11/13 13:40:30 by pjarnac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stddef.h>

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*res;
	size_t	ss;
	size_t	i;

	if (!s || !f)
		return (NULL);
	ss = ft_strlen(s);
	res = (char *)ft_calloc(ss + 1, sizeof (char));
	if (!res)
		return (NULL);
	i = 0;
	while (i < ss)
	{
		res[i] = f((unsigned int)i, s[i]);
		i++;
	}
	return (res);
}
