/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_vector.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjarnac <pjarnac@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 15:57:02 by pjarnac           #+#    #+#             */
/*   Updated: 2025/03/13 15:57:02 by pjarnac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <errno.h>

#include "vector.h"

/*!
 * Create the vector.
 * @return A pointer to the start of the data.
 */
t_vct	vct_create(size_t e_size, void (*del)(void *), int32_t flags)
{
	t_vcthead	*head;

	head = malloc(sizeof (t_vcthead));
	if (!head)
		return (NULL);
	head->capacity = 0;
	head->size = 0;
	head->e_size = e_size;
	head->del = del;
	head->flags = flags;
	return (&head->data);
}

/*!
 * Return a pointer to the vector header.
 * @param vct Current vector.
 * @return Pointer to vector header.
 */
t_vcthead	*get_vcthead(t_vct vct)
{
	return (&((t_vcthead *)vct)[-1]);
}

/*!
 * The vector to free.
 * @param vct Current vector.
 */
void	free_vct(t_vct vct)
{
	free(get_vcthead(vct));
}
