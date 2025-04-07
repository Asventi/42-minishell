/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   int_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjarnac <pjarnac@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 17:49:43 by pjarnac           #+#    #+#             */
/*   Updated: 2025/02/10 17:49:43 by pjarnac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/int_utils.h"
#include "../../includes/formats.h"

int32_t	int_size(int n, t_format *format)
{
	int32_t	i;

	i = 1;
	while (n / 10 != 0)
	{
		n /= 10;
		i++;
	}
	if (format->prec != -1 && i < format->prec)
		i = format->prec;
	return (i);
}

int32_t	uint_size(unsigned int n, t_format *format)
{
	int32_t	i;

	i = 1;
	while (n / 10 > 0)
	{
		n /= 10;
		i++;
	}
	if (format->prec != -1 && i < format->prec)
		i = format->prec;
	return (i);
}

int32_t	hex_size(unsigned int n, t_format *format)
{
	int32_t	i;

	i = 1;
	while (n / 16 > 0)
	{
		n /= 16;
		i++;
	}
	if (format->prec != -1 && i < format->prec)
		i = format->prec;
	return (i);
}

int32_t	ptr_size(uintptr_t n, t_format *format)
{
	int32_t	i;

	i = 1;
	while (n / 16 > 0)
	{
		n /= 16;
		i++;
	}
	if (format->prec != -1 && i < format->prec)
		i = format->prec;
	return (i);
}
