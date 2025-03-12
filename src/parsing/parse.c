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
#include <errno.h>

#include "context.h"
#include "command.h"
#include "libft.h"

int	parse(char *str, t_cmd *cmd, t_context *ctx)
{
	char	**args;

	args = ft_split(str, ' ');
	if (!args[0])
		return (free_split(args), 0);
	cmd->args = args;
	cmd->env = ctx->env;
	if (ft_strncmp(str, "./", 2) != 0)
	{
		if (search_path(args[0], cmd->path) != 0)
			return (errno);
	}
	else
		ft_strlcpy(cmd->path, args[0], PATH_MAX);
	exec_cmd(cmd);
	free_split(args);
	return (0);
}
