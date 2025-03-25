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

#include <stdlib.h>

#include "libft.h"
#include "parsing.h"
#include "constants/operators.h"

static int32_t	put_env(t_token *token, char *envvar, t_context *ctx)
{
	char	*res;

	if (!ft_strcmp(envvar, "?"))
	{
		res = ft_itoa(ctx->last_code);
		if (!res)
			return (-1);
		if (vct_strcatnnull(&token->txt, res) != 0)
			return (free(res), -1);
		free(res);
		return (0);
	}
	res = getenv(envvar);
	if (res)
		if (vct_strcatnnull(&token->txt, res) != 0)
			return (-1);
	return (0);
}

static int32_t	set_env(t_token *token, char **str, t_context *ctx)
{
	char	*envvar;
	int32_t	i;

	(*str)++;
	envvar = vct_create(sizeof (char), 0, DESTROY_ON_FAIL);
	if (!envvar)
		return (-1);
	i = -1;
	while (ft_isalnum((*str)[++i]))
	{
		if (vct_add(&envvar, *str + i) != 0)
			return (-1);
		if (ft_isdigit((*str)[0]) && ++i)
			break ;
	}
	if (**str == '?' && ++i)
		if (vct_add(&envvar, *str) != 0)
			return (-1);
	(*str) += i;
	if (vct_add(&envvar, &(char){0}) != 0)
		return (-1);
	if (put_env(token, envvar, ctx) != 0)
		return (vct_destroy(envvar), -1);
	vct_destroy(envvar);
	return (0);
}

static int32_t	process_token(t_token *token, char *str, t_context *ctx)
{
	char	quote;

	vct_erase(token->txt, 0, (int32_t)vct_size(token->txt));
	quote = 0;
	while (*str)
	{
		if (ft_ischarset(*str, QUOTES) && !quote)
			quote = *str;
		else if (ft_ischarset(*str, QUOTES) && quote == *str)
			quote = 0;
		if (*str == '$' && quote != '\''
			&& (ft_isalnum(str[1]) || str[1] == '?'))
		{
			if (set_env(token, &str, ctx) == -1)
				return (-1);
		}
		else
		{
			if ((*str != quote && !(ft_ischarset(*str, QUOTES) && !quote))
				&& vct_add(&token->txt, str) != 0)
				return (-1);
			str++;
		}
	}
	return (vct_add(&token->txt, &(char){0}));
}

static int32_t	dup_token(t_token *token, t_token *src)
{
	token->txt = vct_create(sizeof (char), 0, 0);
	if (!token->txt)
		return (-1);
	token->type = src->type;
	if (vct_strcpy(&token->txt, src->txt) != 0)
		return (-1);
	return (0);
}

int32_t	expander(t_token **tokens_exp, t_token *tokens, t_context *ctx)
{
	int32_t	i;
	t_token	tk;

	(void)ctx;
	*tokens_exp = vct_create(sizeof (t_token), free_tokenexp, DESTROY_ON_FAIL);
	if (!*tokens_exp)
		return (-1);
	i = -1;
	while (++i < (int32_t)vct_size(tokens))
	{
		if (dup_token(&tk, &tokens[i]) != 0)
			return (vct_destroy(*tokens_exp), -1);
		if (ARG <= tokens[i].type && tokens[i].type <= COMMAND)
			if (process_token(&tk, tokens[i].txt, ctx) != 0)
				return (vct_destroy(*tokens_exp), -1);
		if (vct_add(tokens_exp, &tk) != 0)
			return (-1);
	}
	return (0);
}
