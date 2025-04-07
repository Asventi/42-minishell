/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nseon <nseon@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 10:34:23 by nseon             #+#    #+#             */
/*   Updated: 2025/04/07 14:19:47 by nseon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "context.h"
#include <stdio.h>
#include "env.h"

int	env_cmd(t_context *ctx)
{
	int	i;

	i = 0;
	while (ctx->env[i])
	{
		if (check_form(ctx->env[i]) == 1)
			printf("%s\n", ctx->env[i]);
		i++;
	}
	return (0);
}
