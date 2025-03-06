/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjarnac <pjarnac@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 15:22:09 by pjarnac           #+#    #+#             */
/*   Updated: 2024/11/13 13:40:58 by pjarnac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stddef.h>

void	ft_striteri(char *s, void (*f)(unsigned int, char *))
{
	size_t	ss;
	size_t	i;

	if (!f || !s)
		return ;
	ss = ft_strlen(s);
	i = 0;
	while (i < ss)
	{
		f((unsigned int)i, s + i);
		i++;
	}
}
