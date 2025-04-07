/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjarnac <pjarnac@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 10:44:30 by pjarnac           #+#    #+#             */
/*   Updated: 2025/03/18 10:44:30 by pjarnac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <errno.h>

#include "context.h"
#include "command.h"
#include "libft.h"
#include "errors.h"
#include "parsing.h"
#include "constants/operators.h"

static void	set_quote(char c, char *quote)
{
	if (ft_ischarset(c, QUOTES) && !*quote)
		*quote = c;
	else if (ft_ischarset(c, QUOTES) && *quote == c)
		*quote = 0;
}

static int32_t	set_char(char **res, char *str, char quote)
{
	if (ft_ischarset(*str, WHITESPACES) && !quote)
		return (vct_add(res, "\x1D"));
	return (vct_add(res, str));
}

static char	*spacizer(char *str)
{
	char	*res;
	bool	in_op;
	char	quote;

	in_op = false;
	quote = 0;
	res = vct_create(sizeof (char), 0, DESTROY_ON_FAIL);
	if (!res)
		return (NULL);
	while (*str)
	{
		if (((!in_op && ft_ischarset(*str, OPERATORS))
				|| (in_op && !ft_ischarset(*str, OPERATORS))) && !quote)
			if (vct_add(&res, "\x1D") != 0)
				return (NULL);
		set_quote(*str, &quote);
		in_op = ft_ischarset(*str, OPERATORS);
		if (set_char(&res, str, quote) != 0)
			return (NULL);
		str++;
	}
	vct_add(&res, str);
	return (res);
}

int32_t	tokenize(char ***args, char *str)
{
	str = spacizer(str);
	if (!str)
		return (-1);
	*args = ft_split(str, '\x1D');
	free_vct(str);
	if (!*args)
		return (-1);
	return (0);
}
