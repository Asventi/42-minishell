/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   formats.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjarnac <pjarnac@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 14:01:26 by pjarnac           #+#    #+#             */
/*   Updated: 2025/02/10 14:01:26 by pjarnac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/formats.h"
#include "../includes/flags.h"
#include "libft.h"
#include "../includes/types.h"

#include <stdarg.h>
#include <stdbool.h>
#include <unistd.h>

static void	get_precision(const char **s, t_format *format)
{
	if (**s != '.')
	{
		format->prec = -1;
		return ;
	}
	(*s)++;
	format->prec = ft_atoi(*s);
	while (ft_isdigit(**s))
		(*s)++;
}

static void	get_width(const char **s, t_format *format)
{
	format->width = ft_atoi(*s);
	while (ft_isdigit(**s))
		(*s)++;
}

static bool	get_flag(const char **s, t_format *format)
{
	if (**s == '-')
		format->flags |= MINUS_F;
	else if (**s == '+')
		format->flags |= PLUS_F;
	else if (**s == '#')
		format->flags |= HASH_F;
	else if (**s == ' ')
		format->flags |= BLANK_F;
	else if (**s == '0')
		format->flags |= ZERO_F;
	else
		return (false);
	(*s)++;
	return (true);
}

static void	get_format(const char **s, t_format *format)
{
	while (get_flag(s, format))
		continue ;
	get_width(s, format);
	get_precision(s, format);
}

void	apply_format(int fd, const char **s, int32_t *total, va_list args)
{
	t_format	format;

	ft_bzero(&format, sizeof (t_format));
	get_format(s, &format);
	if (**s == 's')
		str_type(fd, va_arg(args, char *), &format, total);
	else if (**s == 'c')
		char_type(fd, (char) va_arg(args, int), &format, total);
	else if (**s == 'd' || **s == 'i')
		int_type(fd, va_arg(args, int), &format, total);
	else if (**s == 'u')
		uint_type(fd, va_arg(args, unsigned int), &format, total);
	else if (**s == 'x')
		hexmin_type(fd, va_arg(args, unsigned int), &format, total);
	else if (**s == 'X')
		hexmaj_type(fd, va_arg(args, unsigned int), &format, total);
	else if (**s == 'p')
		ptr_type(fd, va_arg(args, uintptr_t), &format, total);
	else if (**s == '%')
		*total += (int32_t) write(fd, "%", 1);
	(*s)++;
}
