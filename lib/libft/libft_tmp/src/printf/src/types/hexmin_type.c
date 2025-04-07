/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hex_type.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjarnac <pjarnac@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 15:05:10 by pjarnac           #+#    #+#             */
/*   Updated: 2025/02/10 15:05:10 by pjarnac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/formats.h"
#include "../../includes/int_utils.h"
#include "../../includes/flags.h"

#include <unistd.h>

#include "../../includes/types.h"

static void	write_num(int fd, unsigned int num, int32_t *total, int32_t prec)
{
	if (num > 15 || prec > 1)
		write_num(fd, num / 16, total, --prec);
	*total += (int32_t) write(fd, &HEX_MIN[num % 16 + 2], 1);
}

static int32_t	calc_spacing(unsigned int n, t_format *format)
{
	int32_t	spacing;
	int32_t	len;

	spacing = 0;
	len = hex_size(n, format);
	if (format->flags & HASH_F && n != 0)
		len += 2;
	if (format->prec == 0 && n == 0)
		len--;
	if (format->prec != -1 && len < format->prec)
		len = format->prec;
	if (format->width > len)
		spacing = format->width - len;
	return (spacing);
}

static void	spacing(int fd, unsigned int num, t_format *format, int32_t *total)
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

void	hexmin_type(int fd, unsigned int n, t_format *format, int32_t *total)
{
	if (format->flags & HASH_F && n != 0
		&& (format->flags & ZERO_F && format->prec == -1))
		*total += (int32_t) write(fd, HEX_MIN, 2);
	if (!(format->flags & MINUS_F))
		spacing(fd, n, format, total);
	if (format->flags & HASH_F && n != 0
		&& (!(format->flags & ZERO_F) || format->prec != -1))
		*total += (int32_t) write(fd, HEX_MIN, 2);
	if (n != 0 || format->prec != 0)
		write_num(fd, n, total, format->prec);
	if (format->flags & MINUS_F)
		spacing(fd, n, format, total);
}
