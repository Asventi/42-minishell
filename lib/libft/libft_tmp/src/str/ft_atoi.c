/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjarnac <pjarnac@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 14:59:17 by pjarnac           #+#    #+#             */
/*   Updated: 2024/12/10 14:34:28 by pjarnac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>

static int	ft_isspace(char c)
{
	return ((9 <= c && c <= 13) || c == ' ');
}

int	ft_atoi(const char *nptr)
{
	int						sign;
	long long int			res;
	int						i;

	sign = 1;
	res = 0;
	i = 0;
	while (ft_isspace(nptr[i]))
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		sign *= -1 * (nptr[i] - 44);
		i++;
	}
	while ('0' <= nptr[i] && nptr[i] <= '9')
	{
		if ((res * 10 + nptr[i] - '0') / 10 != res)
			return (-1 * (sign > 0));
		res = res * 10 + nptr[i] - '0';
		i++;
	}
	return ((int)(sign * res));
}
