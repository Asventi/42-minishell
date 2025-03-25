/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nseon <nseon@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 10:22:03 by nseon             #+#    #+#             */
/*   Updated: 2025/03/25 10:49:41 by nseon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "context.h"
#include "command.h"
#include "libft.h"

int	unset_cmd(t_cmd *cmd, t_context *ctx)
{
	int	i;
	int	j;

	j = 0;
	while (cmd->args)
	{
		i = 0;
		while (ctx->env)
		{
			if (ft_strncmp(cmd->args[j], ctx->env[i], ft_strlen(cmd->args[j])))
				if (ctx->env[i][ft_strlen(cmd->args[j])] == '=')
					vct_delete(ctx->env, i);
			i++;
		}
		j++;
	}
	return (0);
}
