/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_formats.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjarnac <pjarnac@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 16:15:07 by pjarnac           #+#    #+#             */
/*   Updated: 2024/11/25 12:42:59 by pjarnac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	from_char(unsigned char c, int *t)
{
	ft_putchar_fd(c, 1);
	*t += 1;
}

void	from_str(const char *str, int *t)
{
	if (!str)
	{
		ft_putstr_fd("(null)", 1);
		*t += 6;
		return ;
	}
	ft_putstr_fd((char *)str, 1);
	*t += ft_strlen(str);
}

void	from_percent(int *t)
{
	ft_putchar_fd('%', 1);
	*t += 1;
}
