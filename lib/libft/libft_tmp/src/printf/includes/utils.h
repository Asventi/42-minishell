/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjarnac <pjarnac@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 15:10:12 by pjarnac           #+#    #+#             */
/*   Updated: 2025/02/11 15:10:12 by pjarnac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include <stdint.h>

# include "formats.h"

void	str_null_spacing(int fd, t_format *format, int32_t *total);
void	ptr_null_spacing(int fd, t_format *format, int32_t *total);

#endif
