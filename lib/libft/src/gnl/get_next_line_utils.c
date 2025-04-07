/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjarnac <pjarnac@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 13:59:38 by pjarnac           #+#    #+#             */
/*   Updated: 2024/11/28 13:35:51 by pjarnac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdlib.h>

char	*gnl_strchr(char *s, int c)
{
	while (*s)
	{
		if (*s == (unsigned char)c)
			return ((char *)s);
		s++;
	}
	if ((unsigned char)c == 0)
		return ((char *)s);
	else
		return (NULL);
}

size_t	gnl_strlen(char *str)
{
	size_t	c;

	c = 0;
	if (!str)
		return (0);
	while (str[c])
		c++;
	return (c);
}

char	*ft_strndup(char *s, size_t n)
{
	char		*dup;
	size_t		slen;
	size_t		i;

	if (!s)
		return (0);
	slen = gnl_strlen(s);
	if (slen > n)
		slen = n;
	dup = malloc(slen + 1 * sizeof (char));
	if (!dup)
		return (NULL);
	dup[slen] = 0;
	i = 0;
	while (i < slen)
	{
		dup[i] = s[i];
		i++;
	}
	return (dup);
}

int	add_stock(char **stock, char *buf, size_t count)
{
	size_t	i;
	size_t	j;
	size_t	stock_len;
	char	*res;

	stock_len = gnl_strlen(*stock);
	res = malloc(stock_len + count + 1);
	if (!res)
		return (-1);
	res[stock_len + count] = 0;
	i = 0;
	while (i < stock_len)
	{
		res[i] = (*stock)[i];
		i++;
	}
	j = 0;
	while (j < count)
	{
		res[i + j] = buf[j];
		j++;
	}
	free(*stock);
	*stock = res;
	return (0);
}

void	free_stock(char **stock)
{
	free(*stock);
	*stock = 0;
}
