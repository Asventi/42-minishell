/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_del.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjarnac <pjarnac@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 10:44:54 by pjarnac           #+#    #+#             */
/*   Updated: 2025/03/24 10:44:54 by pjarnac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"
#include "libft.h"

void	vct_erase(t_vct	vct, int32_t pos, int32_t n)
{
	int32_t		i;
	t_vcthead	*head;

	head = get_vcthead(vct);
	i = -1;
	if (head->del)
		while (++i < n)
			head->del(head->data + (i + pos) * head->e_size);
	ft_memmove(&head->data[pos * head->e_size],
		&head->data[(pos + n) * head->e_size],
		(head->size - pos - n) * head->e_size);
	head->size -= n;
}

void	vct_delete(t_vct vct, int32_t pos)
{
	vct_erase(vct, pos, 1);
}

void	vct_destroy(t_vct vct)
{
	vct_erase(vct, 0, (int32_t) get_vcthead(vct)->size);
	free_vct(vct);
}
