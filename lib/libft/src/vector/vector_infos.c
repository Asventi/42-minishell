/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_infos.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjarnac <pjarnac@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 18:50:38 by pjarnac           #+#    #+#             */
/*   Updated: 2025/03/13 18:50:38 by pjarnac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>

#include "vector.h"

size_t	vct_size(t_vct vct)
{
	return (get_vcthead(vct)->size);
}

void	set_vct_size(t_vct vct, size_t size)
{
	get_vcthead(vct)->size = size;
}

void	add_vct_size(t_vct vct, size_t size)
{
	get_vcthead(vct)->size += size;
}

size_t	vct_capacity(t_vct vct)
{
	return (get_vcthead(vct)->capacity);
}

/*!
 *
 * @param head Current vector head
 * @return true if vector is full, false if not
 */
bool	is_vct_full(t_vcthead *head)
{
	return (!(head->capacity - head->size));
}
