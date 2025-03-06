/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjarnac <pjarnac@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 15:54:57 by pjarnac           #+#    #+#             */
/*   Updated: 2024/11/12 16:24:04 by pjarnac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*dup;
	int		slen;
	int		i;

	slen = ft_strlen(s);
	dup = ft_calloc(slen + 1, sizeof (char));
	if (!dup)
		return (NULL);
	i = 0;
	while (i < slen)
	{
		dup[i] = s[i];
		i++;
	}
	return (dup);
}
