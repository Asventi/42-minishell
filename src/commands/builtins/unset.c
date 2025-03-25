/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nseon <nseon@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 10:22:03 by nseon             #+#    #+#             */
/*   Updated: 2025/03/25 10:42:08 by nseon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "context.h"
#include "command.h"
#include "libft.h"

int	unset_cmd(t_cmd *cmd, t_context *ctx)
{
	while (cmd->args)
	{
		while (ctx->env)
		{
			if (ft_strncmp(*cmd->args, *ctx->env, ft_strlen(*cmd->args)))
				if (ctx->env[ft_strlen(*cmd->args)] == '=')
					
		}
	}
}
