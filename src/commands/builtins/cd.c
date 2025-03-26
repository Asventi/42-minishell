/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nseon <nseon@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 09:20:31 by nseon             #+#    #+#             */
/*   Updated: 2025/03/21 14:20:51 by nseon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "context.h"
#include <unistd.h>
#include "libft.h"
#include <stdlib.h>
#include "errors.h"
#include "command.h"

int	cd_cmd(t_cmd *cmd)
{
	if (vct_size(cmd->args) > 3)
		return (p_error("cd", NULL, "too many arguments"));
	if (vct_size(cmd->args) == 2 || !ft_strcmp(cmd->args[1], "~"))
	{
		if (chdir(getenv("HOME")) == -1)
			return (p_error("cd", NULL, NULL));
		return (0);
	}
	if (chdir(cmd->args[1]) == -1)
		return (p_error("cd", cmd->args[0], NULL));
	return (0);
}
