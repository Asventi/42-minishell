/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjarnac <pjarnac@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 12:12:40 by pjarnac           #+#    #+#             */
/*   Updated: 2024/11/13 14:24:16 by pjarnac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	calc_alloc(int n)
{
	int	c;

	if (n == 0)
		return (1);
	c = 0;
	if (n < 0)
		c++;
	while (n != 0)
	{
		c++;
		n /= 10;
	}
	return (c);
}

char	*ft_itoa(int n)
{
	char	*res;
	int		size;

	size = calc_alloc(n);
	res = (char *)ft_calloc(size + 1, sizeof (char));
	if (!res)
		return (NULL);
	if (n < 0)
		res[0] = '-';
	if (n == 0)
		res[0] = '0';
	while (n != 0)
	{
		if (n < 0)
			res[size - 1] = n % -10 * -1 + 48;
		else
			res[size - 1] = n % 10 + 48;
		n /= 10;
		size--;
	}
	return (res);
}
