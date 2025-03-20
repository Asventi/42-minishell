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

static void	set_char(char **res, char *str, char quote)
{
	if (*str == ' ' && !quote)
		vct_add(res, "\x1D");
	else
		vct_add(res, str);
}

static char	*spacizer(char *str)
{
	char	*res;
	bool	in_op;
	char	quote;

	in_op = false;
	quote = 0;
	res = create_vector(sizeof (char));
	if (!res)
		return (NULL);
	while (*str)
	{
		if (((!in_op && ft_ischarset(*str, OPERATORS))
				|| (in_op && !ft_ischarset(*str, OPERATORS))) && !quote)
			vct_add(&res, "\x1D");
		if (ft_ischarset(*str, QUOTES) && !quote)
			quote = *str;
		else if (ft_ischarset(*str, QUOTES) && quote == *str)
			quote = 0;
		in_op = ft_ischarset(*str, OPERATORS);
		set_char(&res, str, quote);
		str++;
	}
	vct_add(&res, str);
	return (res);
}

int32_t	tokenize(char ***args, char *str)
{
	int32_t	i;

	i = 0;
	str = spacizer(str);
	if (!str)
		return (-1);
	*args = ft_split(str, '\x1D');
	free_vct(str);
	if (!*args)
		return (-1);
	return (0);
}
