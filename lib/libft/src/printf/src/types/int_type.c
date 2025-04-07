/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   int_type.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjarnac <pjarnac@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 15:04:52 by pjarnac           #+#    #+#             */
/*   Updated: 2025/02/10 15:04:52 by pjarnac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/formats.h"
#include "../../includes/int_utils.h"
#include "../../includes/flags.h"

#include <unistd.h>

#include "../../includes/types.h"

static void	write_num(int fd, long long num, int32_t *total, int32_t prec)
{
	if (num < 0)
		num *= -1;
	if (num > 9 || prec > 1)
		write_num(fd, num / 10, total, --prec);
	*total += (int32_t) write(fd, &DECIMAL[num % 10], 1);
}

static int32_t	calc_spacing(int n, t_format *format)
{
	int32_t	spacing;
	int32_t	len;

	spacing = 0;
	len = int_size(n, format) + (n < 0 || format->flags & PLUS_F
			|| format->flags & BLANK_F);
	if (format->prec == 0 && n == 0)
		len--;
	if (format->prec != -1 && len < format->prec)
		len = format->prec;
	if (format->width > len)
		spacing = format->width - len;
	return (spacing);
}

static void	spacing(int fd, int num, t_format *format, int32_t *total)
{
	int32_t	i;
	int32_t	space;

	space = calc_spacing(num, format);
	i = 0;
	while (i < space)
	{
		if (format->flags & ZERO_F
			&& (!(format->flags & MINUS_F) && format->prec == -1))
			*total += (int32_t) write(fd, "0", 1);
		else
			*total += (int32_t) write(fd, " ", 1);
		i++;
	}
}

static void	decide_spacing(int fd, int num, t_format *format, int32_t *total)
{
	if (format->flags & ZERO_F && format->prec == -1)
	{
		if (num < 0)
			*total += (int32_t) write(fd, "-", 1);
		else if (format->flags & PLUS_F)
			*total += (int32_t) write(fd, "+", 1);
		else if (format->flags & BLANK_F)
			*total += (int32_t) write(fd, " ", 1);
		if (!(format->flags & MINUS_F))
			spacing(fd, num, format, total);
	}
	else
	{
		if (!(format->flags & MINUS_F))
			spacing(fd, num, format, total);
		if (num < 0)
			*total += (int32_t) write(fd, "-", 1);
		else if (format->flags & PLUS_F)
			*total += (int32_t) write(fd, "+", 1);
		else if (format->flags & BLANK_F)
			*total += (int32_t) write(fd, " ", 1);
	}
}

void	int_type(int fd, int n, t_format *format, int32_t *total)
{
	long long	num;

	num = (long long) n;
	decide_spacing(fd, n, format, total);
	if (n != 0 || format->prec != 0)
		write_num(fd, num, total, format->prec);
	if (format->flags & MINUS_F)
		spacing(fd, n, format, total);
}
