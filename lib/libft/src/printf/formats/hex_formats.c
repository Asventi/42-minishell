/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hex_formats.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjarnac <pjarnac@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 10:32:28 by pjarnac           #+#    #+#             */
/*   Updated: 2024/11/25 11:03:31 by pjarnac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	to_hex(unsigned long long int n, char *base, int *t)
{
	if (n / 16 > 0)
		to_hex(n / 16, base, t);
	ft_putchar_fd(base[n % 16], 1);
	*t += 1;
}

void	from_lowhex(unsigned int n, int *t)
{
	to_hex(n, "0123456789abcdef", t);
}

void	from_uphex(unsigned int n, int *t)
{
	to_hex(n, "0123456789ABCDEF", t);
}

void	from_ptr(void *ptr, int *t)
{
	if (!ptr)
	{
		ft_putstr_fd("(nil)", 1);
		*t += 5;
		return ;
	}
	ft_putstr_fd("0x", 1);
	*t += 2;
	to_hex((unsigned long long int)ptr, "0123456789abcdef", t);
}
