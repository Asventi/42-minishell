/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_add.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjarnac <pjarnac@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 17:09:19 by pjarnac           #+#    #+#             */
/*   Updated: 2025/03/13 17:09:19 by pjarnac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <stdio.h>
#include <errno.h>

#include "vector.h"

/*!
 * Return a pointer where you can manually write the next data.
 * @param vctptr A pointer to the vector.
 * @return A pointer to the write destination of the next value.
 */
t_vct	vct_add_dest(t_vctptr vctptr)
{
	t_vct		*vct;
	t_vcthead	*head;

	vct = (t_vct *)vctptr;
	head = get_vcthead(*vct);
	if (is_vct_full(head))
	{
		head = realloc_vct(head);
		if (!head)
			return (NULL);
		*vct = head->data;
	}
	return (&head->data[head->e_size * head->size++]);
}

/*!
 * Add value to the end of vector with the pointer to the value.
 * @param vctptr The pointer to the vector.
 * @param val Pointer to the value.
 * @return code: -1 if failed, 0 if success
 */
int32_t	vct_add(t_vctptr vctptr, void *val)
{
	t_vct	*vct;
	t_vct	*dest;

	vct = (t_vct *)vctptr;
	if (!val)
	{
		if (get_vcthead(*vct)->flags & DESTROY_ON_FAIL)
			vct_destroy(*vct);
		return (-1);
	}
	dest = vct_add_dest(vct);
	if (!dest)
	{
		if (get_vcthead(*vct)->del)
			get_vcthead(*vct)->del(val);
		if (get_vcthead(*vct)->flags & DESTROY_ON_FAIL)
			vct_destroy(*vct);
		return (-1);
	}
	ft_memcpy(dest, val, get_vcthead(*vct)->e_size);
	return (0);
}

/*!
 * Return a pointer where you can manually write the next data.
 * @param vctptr A pointer to the vector.
 * @param i Index position of element.
 * @return A pointer to the write destination of the next value.
 */
t_vct	vct_insert_dest(t_vctptr vctptr, int32_t i)
{
	t_vct		*vct;
	t_vcthead	*head;

	vct = (t_vct *)vctptr;
	head = get_vcthead(*vct);
	if (i >= (int32_t) head->capacity || i < 0)
		return (errno = EINVAL, NULL);
	if (is_vct_full(head))
	{
		head = realloc_vct(head);
		if (!head)
			return (NULL);
		*vct = head->data;
	}
	ft_memmove(&head->data[(i + 1) * head->e_size],
		&head->data[i * head->e_size],
		(head->size - i) * head->e_size);
	head->size += 1;
	return (&head->data[head->e_size * i]);
}

/*!
 * Add value to the end of vector with the pointer to the value.
 * @param vctptr The pointer to the vector.
 * @param val Pointer to the value.
 * @param i Index position of element.
 * @return code: -1 if failed, 0 if success
 */
int32_t	vct_insert(t_vctptr vctptr, void *val, int32_t i)
{
	t_vct	*vct;
	t_vct	*dest;

	vct = (t_vct *)vctptr;
	if (!val)
	{
		if (get_vcthead(*vct)->flags & DESTROY_ON_FAIL)
			vct_destroy(*vct);
		return (-1);
	}
	dest = vct_insert_dest(vct, i);
	if (!dest)
	{
		if (get_vcthead(*vct)->del)
			get_vcthead(*vct)->del(val);
		if (get_vcthead(*vct)->flags & DESTROY_ON_FAIL)
			vct_destroy(*vct);
		return (-1);
	}
	ft_memcpy(dest, val, get_vcthead(*vct)->e_size);
	return (0);
}
