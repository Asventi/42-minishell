/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjarnac <pjarnac@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 14:47:03 by pjarnac           #+#    #+#             */
/*   Updated: 2025/03/12 14:47:03 by pjarnac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>

#include "libft.h"
#include "errors.h"

int	p_error(const char *src)
{
	char	*err;

	err = strerror(errno);
	write(2, src, ft_strlen(src));
	write(2, ": ", 2);
	write(2, err, ft_strlen(err));
	return (0);
}

void	p_errorexit(const char *src)
{
	p_error(src);
	exit(EXIT_FAILURE);
}
