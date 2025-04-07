/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ischarset.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjarnac <pjarnac@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 13:51:37 by pjarnac           #+#    #+#             */
/*   Updated: 2025/03/18 13:51:37 by pjarnac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

bool	ft_ischarset(char c, const char *set)
{
	while (*set)
	{
		if (*set == c)
			return (true);
		set++;
	}
	return (false);
}

bool	ft_isstrcharset(const char *str, const char *set)
{
	while (*str)
	{
		if (ft_ischarset(*str, set))
			return (true);
		str++;
	}
	return (false);
}
