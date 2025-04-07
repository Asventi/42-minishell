/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_type.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjarnac <pjarnac@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 15:05:01 by pjarnac           #+#    #+#             */
/*   Updated: 2025/02/10 15:05:01 by pjarnac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <unistd.h>

#include "../../includes/formats.h"
#include "../../includes/flags.h"
#include "../../includes/utils.h"

static int32_t	calc_spacing(int32_t slen, t_format *format)
{
	int32_t	spacing;

	spacing = 0;
	if (format->prec != -1 && slen > format->prec)
		slen = format->prec;
	if (format->width > slen)
		spacing = format->width - slen;
	return (spacing);
}

static void	spacing(int fd, int32_t n, int32_t *total)
{
	int32_t	i;

	i = 0;
	while (i < n)
	{
		*total += (int32_t) write(fd, " ", 1);
		i++;
	}
}

void	str_type(int fd, char *str, t_format *format, int32_t *total)
{
	int32_t	i;

	if (!str)
	{
		if (!(format->flags & MINUS_F))
			str_null_spacing(fd, format, total);
		if (format->prec == -1 || format->prec >= 6)
			*total += (int32_t) write(fd, "(null)", 6);
		if (format->flags & MINUS_F)
			str_null_spacing(fd, format, total);
		return ;
	}
	if (!(format->flags & MINUS_F))
		spacing(fd, calc_spacing((int32_t) ft_strlen(str), format), total);
	i = -1;
	while (str[++i])
	{
		if (format->prec != -1 && i >= format->prec)
			break ;
		*total += (int32_t) write(fd, &str[i], 1);
	}
	if (format->flags & MINUS_F)
		spacing(fd, calc_spacing((int32_t) ft_strlen(str), format), total);
}
