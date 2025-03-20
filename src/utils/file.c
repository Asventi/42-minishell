/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjarnac <pjarnac@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 19:09:42 by pjarnac           #+#    #+#             */
/*   Updated: 2025/03/20 19:09:42 by pjarnac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>

#include "utils.h"
#include "errors.h"

int32_t	check_file_create(char *str)
{
	int32_t	res;

	res = open(str, O_CREAT, 0644);
	if (res == -1)
		return (p_error(str, 0, 0));
	close(res);
	return (0);
}
