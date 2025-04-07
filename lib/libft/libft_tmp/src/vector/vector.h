/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjarnac <pjarnac@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 15:56:26 by pjarnac           #+#    #+#             */
/*   Updated: 2025/03/13 15:56:26 by pjarnac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_H
# define VECTOR_H

# include <stddef.h>
# include <stdint.h>
# include <stdbool.h>

# define DESTROY_ON_FAIL 1

typedef void	*t_vct;
typedef void	*t_vctptr;
typedef struct s_vcthead
{
	size_t	e_size;
	size_t	size;
	size_t	capacity;
	int32_t	flags;
	void	(*del)(void *);
	uint8_t	data[];
}	t_vcthead;

t_vct		vct_add_dest(t_vctptr vctptr);
t_vct		vct_create(size_t e_size, void (*del)(void *), int32_t flags);
t_vcthead	*get_vcthead(t_vct vct);
t_vcthead	*realloc_vct(t_vcthead *head);
void		free_vct(t_vct vct);
int32_t		vct_add(t_vctptr vctptr, void *val);
bool		is_vct_full(t_vcthead *head);
size_t		vct_size(t_vct vct);
size_t		vct_capacity(t_vct vct);
int32_t		vct_allocate(t_vctptr vctptr, size_t size);
int32_t		vct_insert(t_vctptr vctptr, void *val, int32_t i);
t_vct		vct_insert_dest(t_vctptr vctptr, int32_t i);
void		add_vct_size(t_vct vct, size_t size);
void		set_vct_size(t_vct vct, size_t size);
void		vct_erase(t_vct	vct, int32_t pos, int32_t n);
void		vct_delete(t_vct vct, int32_t pos);
void		vct_destroy(t_vct vct);

int32_t		vct_strcat(t_vctptr vctptr, char *str);
int32_t		vct_strcpy(t_vctptr vctptr, char *str);
int32_t		vct_strcatnnull(t_vctptr vctptr, char *str);

#endif
