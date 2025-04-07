/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nseon <nseon@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 18:30:39 by pjarnac           #+#    #+#             */
/*   Updated: 2025/04/01 11:42:18 by nseon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (((unsigned char)s1[i] == (unsigned char)s2[i])
		&& (s1[i] != '\0' && s2[i] != '\0'))
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

static void	ft_swap(char **a, char **b)
{
	char	*buf;

	buf = *a;
	*a = *b;
	*b = buf;
}

static int	get_pivot(char **tab, int first, int last)
{
	int	i;
	int	j;

	i = first;
	j = first;
	while (i < last)
	{
		if (ft_strcmp(tab[i], tab[last]) <= 0)
		{
			ft_swap(&tab[i], &tab[j]);
			j++;
		}
		i++;
	}
	ft_swap(&tab[last], &tab[j]);
	return (j);
}

void	sort(char **tab, int first, int last)
{
	int	pivot;

	if (first <= last)
	{
		pivot = get_pivot(tab, first, last);
		sort(tab, first, pivot - 1);
		sort(tab, pivot + 1, last);
	}
}
