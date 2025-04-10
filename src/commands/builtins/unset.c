/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nseon <nseon@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 10:22:03 by nseon             #+#    #+#             */
/*   Updated: 2025/03/25 13:40:04 by nseon            ###   ########.fr       */
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
	while (cmd->args[j])
	{
		i = 0;
		while (ctx->env[i])
		{
			if (!ft_strncmp(cmd->args[j], ctx->env[i], ft_strlen(cmd->args[j])))
				if (ctx->env[i][ft_strlen(cmd->args[j])] == '='
						|| ctx->env[i][ft_strlen(cmd->args[j])] == '\0')
					vct_delete(ctx->env, i);
			i++;
		}
		j++;
	}
	return (0);
}
