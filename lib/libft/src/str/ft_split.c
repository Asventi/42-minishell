/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjarnac <pjarnac@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 15:30:46 by pjarnac           #+#    #+#             */
/*   Updated: 2024/11/12 17:37:56 by pjarnac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void	free_split(char **tab)
{
	int	i;

	i = 0;
	while (tab[i] != 0)
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

static char	**free_all(char **res, int c)
{
	int	i;

	i = 0;
	while (i < c)
	{
		free(res[i]);
		i++;
	}
	free(res);
	return (NULL);
}

static int	calc_alloc(char const *s, char c)
{
	int	in_word;
	int	count;

	in_word = 0;
	count = 0;
	while (*s)
	{
		if (!in_word && *s != c)
		{
			count++;
			in_word = 1;
		}
		else if (in_word && *s == c)
			in_word = 0;
		s++;
	}
	return (count);
}

static char	*split_strdup(char const *s, char c)
{
	char	*dup;
	int		i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	dup = ft_calloc(i + 1, sizeof (char));
	if (!dup)
		return (NULL);
	i = 0;
	while (s[i] && s[i] != c)
	{
		dup[i] = s[i];
		i++;
	}
	return (dup);
}

char	**ft_split(char const *s, char c)
{
	int		in_word;
	int		count;
	char	**res;

	res = ft_calloc(calc_alloc(s, c) + 1, sizeof (char *));
	if (!res)
		return (NULL);
	in_word = 0;
	count = 0;
	while (*s)
	{
		if (!in_word && *s != c)
		{
			in_word = 1;
			res[count] = split_strdup(s, c);
			if (!res[count])
				return (free_all(res, count));
			count++;
		}
		else if (in_word && *s == c)
			in_word = 0;
		s++;
	}
	return (res);
}
