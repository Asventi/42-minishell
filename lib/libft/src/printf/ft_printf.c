/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjarnac <pjarnac@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 10:55:56 by pjarnac           #+#    #+#             */
/*   Updated: 2024/11/25 12:41:36 by pjarnac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include "./formats/formats.h"
#include "libft.h"

int	ft_printf(const char *s, ...)
{
	va_list	args;
	char	*str;
	int		total;

	if (!s)
		return (-1);
	total = 0;
	str = (char *)s;
	va_start(args, s);
	while (*str)
	{
		if (*str == '%')
		{
			str++;
			process_format(&str, &args, &total);
		}
		else
		{
			ft_putchar_fd(*str, 1);
			total++;
			str++;
		}
	}
	va_end(args);
	return (total);
}
