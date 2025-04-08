/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nseon <nseon@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 09:44:58 by nseon             #+#    #+#             */
/*   Updated: 2025/04/07 13:48:22 by nseon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "command.h"
#include "context.h"
#include "libft.h"
#include "errors.h"
#include <stdlib.h>

static bool	isnum(char *str)
{
	if (*str == '+' || *str == '-')
		str++;
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (0);
		++str;
	}
	return (1);
}

int	exit_cmd(t_cmd *cmd, t_context *ctx)
{
	printf("exit\n");
	if (vct_size(cmd->args) > 2 && isnum(cmd->args[1]))
	{
		if (vct_size(cmd->args) == 3)
		{
			ctx->last_code = ft_atoi(cmd->args[1]);
			return (EXIT);
		}
		p_error("exit", NULL, "too many arguments");
		cmd->path[0] = 'l';
		return (1);
	}
	if (vct_size(cmd->args) >= 3)
	{
		ctx->last_code = 2;
		p_error("exit", cmd->args[1], "numeric argument required");
	}
	return (EXIT);
}
