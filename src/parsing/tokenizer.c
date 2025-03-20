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

static char	*spacizer(char *str)
{
	char	*res;
	bool	in_op;
	char	quote;

	in_op = false;
	quote = 0;
	res = create_vector(sizeof (char));
	while (*str)
	{
		if (((!in_op && ft_ischarset(*str, OPERATORS))
			|| (in_op && !ft_ischarset(*str, OPERATORS))) && !quote)
			vct_add(&res, " ");
		if (ft_ischarset(*str, QUOTES) && !quote)
			quote = *str;
		else if (ft_ischarset(*str, QUOTES) && quote == *str)
			quote = 0;
		in_op = ft_ischarset(*str, OPERATORS);
		vct_add(&res, str);
		str++;
	}
	vct_add(&res, str);
	return (res);
}

char	**tokenize(char *str)
{
	char	**args;
	int32_t	i;

	i = 0;
	str = spacizer(str);

	if (!str)
		return (0);
	printf("%s\n", str);
	return (args);
}
