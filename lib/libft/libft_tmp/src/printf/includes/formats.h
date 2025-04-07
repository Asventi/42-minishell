/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   formats.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjarnac <pjarnac@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 14:02:01 by pjarnac           #+#    #+#             */
/*   Updated: 2025/02/10 14:02:01 by pjarnac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FORMATS_H
# define FORMATS_H

# include <stdint.h>
# include <stdarg.h>

typedef struct s_format
{
	int32_t	width;
	int32_t	prec;
	int8_t	flags;
}	t_format;

void	apply_format(int fd, const char **s, int32_t *total, va_list args);

#endif
