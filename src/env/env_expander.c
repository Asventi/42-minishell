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

#include <stdlib.h>

#include "libft.h"
#include "context.h"
#include "env.h"
#include "errors.h"

int32_t	expand_envvar_quote(char **res, char *envname, t_context *ctx)
{
	char	*envvar;

	envvar = ft_getenv(envname, ctx);
	if (envvar == NULL)
		return (0);
	if (vct_strcatnnull(res, envvar) == -1)
		return (FATAL);
	return (0);
}

static int32_t	add_word(char **res, char *envvar, bool first)
{
	if (!first && vct_add(res, &(char){' '}) == -1)
		return (FATAL);
	if (vct_add(res, &(char){'\''}) == -1)
		return (FATAL);
	if (vct_strcatnnull(res, envvar) == -1)
		return (FATAL);
	if (vct_strcatnnull(res, "\'") == -1)
		return (FATAL);
	return (0);
}

int32_t	expand_envvar_trim(char **res, char *envname, t_context *ctx)
{
	char	*envvar;
	char	**env_split;
	int32_t	i;

	envvar = ft_getenv_trim(envname, ctx);
	if (!envvar)
		return (0);
	env_split = ft_split(envvar, ' ');
	free(envvar);
	if (env_split == 0)
		return (FATAL);
	i = -1;
	while (env_split[++i])
	{
		if (add_word(res, env_split[i], i == 0) == -1)
			return (free_split(env_split), FATAL);
	}
	free_split(env_split);
	return (0);
}

int32_t	expand_last_code(char **res, t_context *ctx)
{
	char	*code;

	code = ft_itoa(ctx->last_code);
	if (!code)
		return (FATAL);
	if (vct_strcatnnull(res, code) == -1)
		return (free(code), FATAL);
	free(code);
	return (0);
}
