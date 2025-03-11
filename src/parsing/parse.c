/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjarnac <pjarnac@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 14:33:43 by pjarnac           #+#    #+#             */
/*   Updated: 2025/03/10 14:33:43 by pjarnac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

#include "context.h"
#include "command.h"
#include "libft.h"

int	parse(char *str, t_cmd *cmd, t_context *ctx)
{
	char	**args;

	args = ft_split(str, ' ');
	cmd->args = args;
	cmd->env = ctx->env;
	if (ft_strncmp(str, "./", 2) == 0)
	{
		printf("blc\n");
	}
	else
	{
		search_path(args[0], cmd->path);
		exec_cmd(cmd);
	}
	return (0);
}
