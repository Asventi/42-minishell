/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nseon <nseon@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 10:05:50 by nseon             #+#    #+#             */
/*   Updated: 2025/03/27 11:18:04 by nseon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.h"
#include <unistd.h>
#include "context.h"

int	pipex(t_cmd *cmd, t_context *ctx)
{
	int	pipefd[2];
	int	i;

	i = 0;
	if (pipe(pipefd) == -1)
		return (-1);
	if (dup2(pipefd[1], 1))
		return (-1);
	if (dup2(pipefd[0], 0))
		return (-1);
	while (i < vct_size(cmd))
	{
		if (is_builtins(cmd->path))
			return (launch_builtins(cmd, ctx));
	}
}
