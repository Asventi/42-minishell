/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nseon <nseon@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 09:44:58 by nseon             #+#    #+#             */
/*   Updated: 2025/04/02 16:17:53 by nseon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "command.h"
#include "context.h"
#include "libft.h"
#include "errors.h"

static bool	isnum(char *str)
{
	while (str)
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
	if (isnum(cmd->args[1]))
	{
		if (vct_size(cmd->args) == 3)
		{
			ctx->last_code = ft_atoi(cmd->args[1]);
			return (EXIT);
		}
		else
			return (p_error("exit", NULL, "too many arguments"));
	}
	if (vct_size(cmd->args) >= 3)
	{
		ctx->last_code = 2;
		p_error("exit", cmd->args[1], "numeric argument required");
	}
	return (EXIT);
}

//TODO: Exit avec des arguments, le code de sortie est celui specifie si yen a un, si plusieurs et chiffre en derniere on exit mais avec 2
// sinon si lettre en dernier exit pas et message derreure
