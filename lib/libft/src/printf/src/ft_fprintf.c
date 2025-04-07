/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjarnac <pjarnac@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 10:55:56 by pjarnac           #+#    #+#             */
/*   Updated: 2024/11/25 12:41:36 by pjarnac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/formats.h"

#include <stdarg.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int	ft_fprintf(int fd, const char *s, ...)
{
	int32_t		total;
	va_list		args;

	if (!s)
		return (-1);
	total = 0;
	va_start(args, s);
	while (*s)
	{
		if (*s == '%')
		{
			s++;
			apply_format(fd, &s, &total, args);
		}
		else
		{
			write(fd, s, 1);
			total++;
			s++;
		}
	}
	va_end(args);
	return (total);
}
