/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjarnac <pjarnac@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 15:48:00 by pjarnac           #+#    #+#             */
/*   Updated: 2025/03/20 15:48:00 by pjarnac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <stdlib.h>

#include "env.h"
#include "libft.h"
#include "errors.h"
#include "parsing.h"
#include "constants/operators.h"

static void	set_quotes(char c, int32_t *quote)
{
	if (*quote == 0 && ft_ischarset(c, QUOTES))
		*quote = (int32_t)c;
	else if (*quote != 0 && *quote == c)
		*quote = 0;
}

static int32_t	get_var(char **res, char **str)
{
	int32_t	i;

	*res = vct_create(sizeof (char), 0, DESTROY_ON_FAIL);
	if (!*res)
		return (-1);
	i = -1;
	while (ft_isalnum((*str)[++i]))
	{
		if (vct_add(res, *str + i) != 0)
			return (-1);
		if (ft_isdigit((*str)[0]) && ++i)
			break ;
	}
	if (**str == '?' && ++i)
		if (vct_add(res, *str) != 0)
			return (-1);
	(*str) += i;
	if (vct_add(res, &(char){0}) != 0)
		return (-1);
	return (0);
}

static int32_t	check_var(char **res, char **str,
					int32_t quote, t_context *ctx)
{
	char	*envname;
	int32_t	ret;

	(*str)++;
	if (get_var(&envname, str) == -1)
		return (free_vct(*res), FATAL);
	if (!envname[0] && **str != '\'' && **str != '\"')
		ret = vct_add(res, &(char){'$'});
	else if (envname[0] == '?')
		ret = expand_last_code(res, ctx);
	else if (quote != 0)
		ret = expand_envvar_quote(res, envname, ctx);
	else
		ret = expand_envvar_trim(res, envname, ctx);
	free_vct(envname);
	return (ret);
}

int32_t	expand(char **res, char *str, t_context *ctx)
{
	int32_t	quote;

	*res = vct_create(sizeof (char), 0, DESTROY_ON_FAIL);
	if (!*res)
		return (FATAL);
	quote = 0;
	while (*str)
	{
		set_quotes(*str, &quote);
		if (*str == '$' && quote != '\'')
		{
			if (check_var(res, &str, quote, ctx) == -1)
				return (FATAL);
		}
		else
		{
			if (vct_add(res, str) == -1)
				return (FATAL);
			str++;
		}
	}
	if (vct_add(res, &(char){0}) == -1)
		return (FATAL);
	return (0);
}
