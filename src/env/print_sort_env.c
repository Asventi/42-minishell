/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_sort_env.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nseon <nseon@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 11:55:03 by nseon             #+#    #+#             */
/*   Updated: 2025/04/07 14:22:19 by nseon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "context.h"
#include "libft.h"
#include <unistd.h>

int	print_and_sort(t_context *ctx)
{
	int	j;
	int	check;
	int	i;

	sort(ctx->env, 0, (int32_t)vct_size(ctx->env) - 2);
	i = -1;
	while (++i < (int32_t)vct_size(ctx->env) - 1)
	{
		j = -1;
		check = 0;
		ft_printf("declare -x ");
		while (ctx->env[i][++j])
		{
			write(1, &ctx->env[i][j], 1);
			if (!check && ctx->env[i][j] == '=')
			{
				write(1, "\"", 1);
				check = 1;
			}
		}
		if (check)
			write(1, "\"", 1);
		write(1, "\n", 1);
	}
	return (0);
}
