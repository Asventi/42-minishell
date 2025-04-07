/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_str.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjarnac <pjarnac@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 14:33:13 by pjarnac           #+#    #+#             */
/*   Updated: 2025/03/25 14:33:13 by pjarnac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"

int32_t	vct_strcat(t_vctptr vctptr, char *str)
{
	char	**vct;

	vct = (char **)vctptr;
	if (vct_size(*vct) > 0)
		if ((*vct)[vct_size(*vct) - 1] == 0)
			vct_delete(*vct, (int32_t)vct_size(*vct) - 1);
	while (*str)
	{
		if (vct_add(vct, str) != 0)
			return (-1);
		str++;
	}
	if (vct_add(vct, &(char){0}) != 0)
		return (-1);
	return (0);
}

int32_t	vct_strcatnnull(t_vctptr vctptr, char *str)
{
	char	**vct;

	vct = (char **)vctptr;
	if (vct_size(*vct) > 0)
		if ((*vct)[vct_size(*vct) - 1] == 0)
			vct_delete(*vct, (int32_t)vct_size(*vct) - 1);
	while (*str)
	{
		if (vct_add(vct, str) != 0)
			return (-1);
		str++;
	}
	return (0);
}

int32_t	vct_strcpy(t_vctptr vctptr, char *str)
{
	char	**vct;

	vct = (char **)vctptr;
	vct_erase(*vct, 0, (int32_t)vct_size(*vct));
	while (*str)
	{
		if (vct_add(vct, str) != 0)
			return (-1);
		str++;
	}
	if (vct_add(vct, &(char){0}) != 0)
		return (-1);
	return (0);
}
