/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nseon <nseon@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 09:20:31 by nseon             #+#    #+#             */
/*   Updated: 2025/03/20 11:47:03 by nseon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "context.h"
#include <unistd.h>
#include "libft.h"
#include <errno.h>
#include <stdlib.h>

int	cd_cmd(t_context *context, char *dest)
{
	if (!dest)
	{
		if (chdir(getenv("HOME")) == -1)
			return (errno);
		return (0);
	}
	if (chdir(dest) == -1)
		return (errno);
	getcwd(context->path, PATH_MAX);
	return (0);
}
