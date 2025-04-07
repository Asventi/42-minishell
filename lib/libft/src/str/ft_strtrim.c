/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjarnac <pjarnac@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 11:52:12 by pjarnac           #+#    #+#             */
/*   Updated: 2024/11/12 16:38:57 by pjarnac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stddef.h>

static int	check_char(char c, char const *set)
{
	while (*set)
	{
		if (c == *set)
			return (1);
		set++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		start;
	int		slen;
	int		i;
	char	*res;

	if (!s1 || !set)
		return (NULL);
	start = 0;
	while (s1[start] && check_char(s1[start], set))
		start++;
	slen = ft_strlen(s1);
	while ((slen != 0 && start != slen)
		&& (s1[slen - 1] && check_char(s1[slen - 1], set)))
		slen--;
	res = (char *)ft_calloc(slen - start + 1, sizeof (char));
	if (!res)
		return (NULL);
	i = -1;
	while (start < slen)
	{
		res[++i] = s1[start];
		start++;
	}
	return (res);
}
