/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pointer_type.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjarnac <pjarnac@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 15:05:50 by pjarnac           #+#    #+#             */
/*   Updated: 2025/02/10 15:05:50 by pjarnac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

#include "../../includes/formats.h"
#include "../../includes/int_utils.h"
#include "../../includes/flags.h"
#include "../../includes/types.h"
#include "../../includes/utils.h"

static void	write_num(int fd, uintptr_t num, int32_t *total, int32_t prec)
{
	if (num > 15 || prec > 1)
		write_num(fd, num / 16, total, --prec);
	*total += (int32_t) write(fd, &HEX_MIN[num % 16 + 2], 1);
}

static int32_t	calc_spacing(uintptr_t n, t_format *format)
{
	int32_t	spacing;
	int32_t	len;

	spacing = 0;
	len = ptr_size(n, format);
	if (format->flags & PLUS_F || format->flags & BLANK_F)
		len++;
	if (format->flags & HASH_F)
		len += 2;
	if (format->prec == 0)
		len--;
	if (format->prec != -1 && len < format->prec)
		len = format->prec;
	if (format->width > len)
		spacing = format->width - len;
	return (spacing);
}

static void	spacing(int fd, uintptr_t num, t_format *format, int32_t *total)
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

static void	decide_spacing(int fd, uintptr_t num,
	t_format *format, int32_t *total)
{
	if (format->flags & ZERO_F && format->prec == -1)
	{
		if (format->flags & PLUS_F)
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
		if (format->flags & PLUS_F)
			*total += (int32_t) write(fd, "+", 1);
		else if (format->flags & BLANK_F)
			*total += (int32_t) write(fd, " ", 1);
	}
}

void	ptr_type(int fd, uintptr_t ptr, t_format *format, int32_t *total)
{
	format->flags |= HASH_F;
	if (ptr == 0)
	{
		if (!(format->flags & MINUS_F))
			ptr_null_spacing(fd, format, total);
		*total += (int32_t) write(fd, "(nil)", 5);
		if (format->flags & MINUS_F)
			ptr_null_spacing(fd, format, total);
		return ;
	}
	if (format->flags & HASH_F
		&& (format->flags & ZERO_F && format->prec == -1))
		*total += (int32_t) write(fd, HEX_MIN, 2);
	decide_spacing(fd, ptr, format, total);
	if (format->flags & HASH_F
		&& (!(format->flags & ZERO_F) || format->prec != -1))
		*total += (int32_t) write(fd, HEX_MIN, 2);
	write_num(fd, ptr, total, format->prec);
	if (format->flags & MINUS_F)
		spacing(fd, ptr, format, total);
}
