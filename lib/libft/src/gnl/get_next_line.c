/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjarnac <pjarnac@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 13:59:17 by pjarnac           #+#    #+#             */
/*   Updated: 2024/11/28 13:36:20 by pjarnac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "get_next_line.h"

static char	*get_from_stock(char *stock)
{
	char	*res;
	char	*delimiter;

	if (!stock)
		return (0);
	delimiter = gnl_strchr(stock, '\n');
	if (!delimiter)
		return (0);
	res = ft_strndup(stock, (size_t)(delimiter - stock + 1));
	if (!res)
		return (stock);
	return (res);
}

static int	remove_from_stock(char **stock, bool end)
{
	char	*res;
	char	*delimiter;

	delimiter = gnl_strchr(*stock, '\n');
	if (end && (!delimiter || gnl_strlen(delimiter + 1) == 0))
	{
		free_stock(stock);
		return (0);
	}
	if (!delimiter)
		return (0);
	res = ft_strndup(delimiter + 1, gnl_strlen(delimiter + 1));
	if (!res)
		return (-1);
	free(*stock);
	*stock = res;
	return (0);
}

static char	*get_line(char *buf, ssize_t count)
{
	static char	*stock;
	char		*line;

	if (count < 0)
		return (free_stock(&stock), buf);
	if ((!stock || stock[0] == 0) && count == 0)
		return (free_stock(&stock), (char *)0);
	if (count != 0)
		if (add_stock(&stock, buf, count) == -1)
			return (free_stock(&stock), buf);
	line = get_from_stock(stock);
	if (line == stock)
		return (buf);
	if (!line && (count < BUFFER_SIZE))
	{
		line = ft_strndup(stock, gnl_strlen(stock));
		free_stock(&stock);
		if (!line)
			return (buf);
	}
	else if (line)
		if (remove_from_stock(&stock, (count < BUFFER_SIZE)) == -1)
			return (free(line), buf);
	return (line);
}

char	*get_next_line(int fd)
{
	char	*buf;
	char	*line;
	ssize_t	res;

	line = 0;
	while (!line)
	{
		buf = malloc(BUFFER_SIZE * sizeof (char));
		if (!buf)
			return (get_line(0, -1), (char *)0);
		res = read(fd, buf, BUFFER_SIZE);
		line = get_line(buf, res);
		if (line == buf)
		{
			get_line(0, -1);
			free(buf);
			return (0);
		}
		free(buf);
		if (!line && res <= 0)
			return (0);
	}
	return (line);
}
