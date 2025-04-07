/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_allocs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjarnac <pjarnac@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 18:25:51 by pjarnac           #+#    #+#             */
/*   Updated: 2025/03/13 18:25:51 by pjarnac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "vector.h"
#include "libft.h"

/*!
 * Realloc and copy old vector content with capacity multiplied by 2,
 * or set to 1 if it were at 0.
 * @param head Current vector header.
 * @return Newly allocated vector.
 */
t_vcthead	*realloc_vct(t_vcthead *head)
{
	t_vcthead	*new_head;
	size_t		new_capacity;

	if (head->capacity == 0)
		new_capacity = 1;
	else
		new_capacity = head->capacity * 2;
	new_head = ft_realloc(head, sizeof (t_vcthead) + head->capacity
			* head->e_size, sizeof (t_vcthead) + new_capacity * head->e_size);
	if (!new_head)
	{
		if (head->flags & DESTROY_ON_FAIL)
			vct_destroy(&head->data);
		return (NULL);
	}
	new_head->capacity = new_capacity;
	return (new_head);
}

/*!
 * Allocate new space for the vector, in elements, not in octets.
 * @param vctptr Pointer to the vector
 * @param size Number of element to allocate room for.
 * @return code: -1 if failed, 0 if success
 */
int32_t	vct_allocate(t_vctptr vctptr, size_t size)
{
	t_vct		*vct;
	t_vcthead	*new_head;
	t_vcthead	*head;
	size_t		new_capacity;

	vct = (t_vct *)vctptr;
	head = get_vcthead(*vct);
	new_capacity = head->capacity + size;
	new_head = ft_realloc(head, sizeof (t_vcthead) + head->capacity
			* head->e_size, sizeof (t_vcthead) + new_capacity * head->e_size);
	if (!new_head)
		return (vct_destroy(*vct), -1);
	new_head->capacity = new_capacity;
	*vct = &new_head->data;
	return (0);
}
