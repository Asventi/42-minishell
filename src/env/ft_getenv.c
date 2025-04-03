/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjarnac <pjarnac@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 17:49:01 by pjarnac           #+#    #+#             */
/*   Updated: 2025/03/25 17:49:01 by pjarnac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "context.h"
#include "libft.h"
#include "constants/operators.h"

char	*ft_getenv(char *name, t_context *ctx)
{
	int32_t	i;

	i = -1;
	while (ctx->env[++i])
	{
		if (!ft_strncmp(name, ctx->env[i], ft_strlen(name)))
		{
			if (ctx->env[i][ft_strlen(name)] == '=')
				return (ctx->env[i] + ft_strlen(name) + 1);
		}
	}
	return (NULL);
}

char	*ft_getenv_trim(char *name, t_context *ctx)
{
	char	*envvar;
	char	*res;

	envvar = ft_getenv(name, ctx);
	if (envvar == NULL)
		return (NULL);
	res = ft_strtrim(envvar, WHITESPACES);
	if (!res)
		return (NULL);
	return (res);
}
