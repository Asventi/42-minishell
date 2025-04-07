/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjarnac <pjarnac@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 15:05:59 by pjarnac           #+#    #+#             */
/*   Updated: 2025/02/10 15:05:59 by pjarnac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_H
# define TYPES_H

# define HEX_MIN "0x0123456789abcdef"
# define HEX_MAJ "0X0123456789ABCDEF"
# define DECIMAL "0123456789"

# include "formats.h"

void	str_type(int fd, char *str, t_format *format, int32_t *total);
void	char_type(int fd, char c, t_format *format, int32_t *total);
void	int_type(int fd, int n, t_format *format, int32_t *total);
void	uint_type(int fd, unsigned int n, t_format *format, int32_t *total);
void	hexmin_type(int fd, unsigned int n, t_format *format, int32_t *total);
void	hexmaj_type(int fd, unsigned int n, t_format *format, int32_t *total);
void	ptr_type(int fd, uintptr_t ptr, t_format *format, int32_t *total);

#endif
