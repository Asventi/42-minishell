/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_expander.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjarnac <pjarnac@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 11:03:28 by pjarnac           #+#    #+#             */
/*   Updated: 2025/04/01 11:03:28 by pjarnac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "context.h"
#include "errors.h"

int32_t	expand_envvar(char **res, char *str, t_context *ctx)
{
	*res = vct_create(sizeof (char), 0, DESTROY_ON_FAIL);
	if (!*res)
		return (FATAL);

	return (0);
}
