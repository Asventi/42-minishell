/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   int_utils.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjarnac <pjarnac@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 17:51:02 by pjarnac           #+#    #+#             */
/*   Updated: 2025/02/10 17:51:02 by pjarnac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INT_UTILS_H
# define INT_UTILS_H

# include <stdint.h>

# include "formats.h"

int32_t	int_size(int n, t_format *format);
int32_t	uint_size(unsigned int n, t_format *format);
int32_t	hex_size(unsigned int n, t_format *format);
int32_t	ptr_size(uintptr_t n, t_format *format);

#endif
