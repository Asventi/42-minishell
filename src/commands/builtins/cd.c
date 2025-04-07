/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nseon <nseon@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 09:20:31 by nseon             #+#    #+#             */
/*   Updated: 2025/04/07 16:31:14 by nseon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "context.h"
#include <unistd.h>
#include "libft.h"
#include <stdlib.h>
#include "errors.h"
#include "command.h"
#include "env.h"

int	cd_cmd(t_cmd *cmd, t_context *ctx)
{
	char	oldpwd[PATH_MAX];

	if (vct_size(cmd->args) > 3)
		return (p_error("cd", NULL, "too many arguments"), 1);
	else if (vct_size(cmd->args) == 2 || !ft_strcmp(cmd->args[1], "~"))
	{
		if (chdir(ft_getenv("HOME", ctx)) == -1)
			return (p_error("cd", NULL, NULL), 1);
	}
	else if (chdir(cmd->args[1]) == -1)
		return (p_error("cd", cmd->args[1], NULL), 1);
	return (update_pwd(ctx, cmd->args[1]));
}
