/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nseon <nseon@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 10:34:23 by nseon             #+#    #+#             */
/*   Updated: 2025/03/25 11:22:16 by nseon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "context.h"
#include "libft.h"
#include <stdio.h>

int	env_cmd(t_context *ctx)
{
	int	i;

	i = 0;
	while (ctx->env[i])
	{
		printf("%s\n", ctx->env[i]);
		i++;
	}
	return (0);
}
