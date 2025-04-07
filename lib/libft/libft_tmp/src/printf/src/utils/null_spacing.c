/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   null_spacing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjarnac <pjarnac@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 15:10:01 by pjarnac           #+#    #+#             */
/*   Updated: 2025/02/11 15:10:01 by pjarnac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

#include "../../includes/formats.h"

void	ptr_null_spacing(int fd, t_format *format, int32_t *total)
{
	int32_t	spacing;

	spacing = 0;
	if (5 < format->width)
		spacing = format->width - 5;
	while (spacing > 0)
	{
		*total += (int32_t) write(fd, " ", 1);
		--spacing;
	}
}

void	str_null_spacing(int fd, t_format *format, int32_t *total)
{
	int32_t	spacing;

	spacing = 0;
	if (6 < format->width)
		spacing = format->width - 6;
	if (format->prec != -1 && format->prec < 6)
		spacing = format->width;
	while (spacing > 0)
	{
		*total += (int32_t) write(fd, " ", 1);
		--spacing;
	}
}
