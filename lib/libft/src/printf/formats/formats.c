/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   formats.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjarnac <pjarnac@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 14:00:59 by pjarnac           #+#    #+#             */
/*   Updated: 2024/11/25 12:42:02 by pjarnac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "formats.h"
#include <stdarg.h>

static bool	is_flag(char c, char *flags)
{
	while (*flags)
	{
		if (c == *flags)
			return (true);
		flags++;
	}
	return (false);
}

static void	apply_format(char t, va_list *args, int *total)
{
	if (t == 'd' || t == 'i')
		from_int(va_arg(*args, int), total);
	else if (t == 'c')
		from_char(va_arg(*args, int), total);
	else if (t == 'u')
		from_uint(va_arg(*args, unsigned int), total);
	else if (t == 's')
		from_str(va_arg(*args, const char *), total);
	else if (t == 'x')
		from_lowhex(va_arg(*args, unsigned int), total);
	else if (t == 'X')
		from_uphex(va_arg(*args, unsigned int), total);
	else if (t == 'p')
		from_ptr(va_arg(*args, void *), total);
	else if (t == '%')
		from_percent(total);
}

void	process_format(char **idx, va_list *args, int *total)
{
	char	type;

	type = 0;
	if (is_flag(**idx, "cspdiuxX%"))
	{
		type = **idx;
		apply_format(type, args, total);
		*idx = *idx + 1;
	}
	else
	{
		ft_putchar_fd('%', 1);
	}
}
