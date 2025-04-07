/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char_type.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjarnac <pjarnac@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 15:04:42 by pjarnac           #+#    #+#             */
/*   Updated: 2025/02/10 15:04:42 by pjarnac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

#include "../../includes/types.h"
#include "../../includes/flags.h"

static int32_t	calc_spacing(t_format *format)
{
	int32_t	spacing;
	int32_t	len;

	spacing = 0;
	len = 1;
	if (format->width > len)
		spacing = format->width - len;
	return (spacing);
}

static void	spacing(int fd, t_format *format, int32_t *total)
{
	int32_t	i;
	int32_t	space;

	space = calc_spacing(format);
	i = 0;
	while (i < space)
	{
		*total += (int32_t) write(fd, " ", 1);
		i++;
	}
}

void	char_type(int fd, char c, t_format *format, int32_t *total)
{
	if (!(format->flags & MINUS_F))
		spacing(fd, format, total);
	*total += (int32_t) write(fd, &c, 1);
	if (format->flags & MINUS_F)
		spacing(fd, format, total);
}
