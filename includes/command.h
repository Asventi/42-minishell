/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nseon <nseon@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 13:49:47 by pjarnac           #+#    #+#             */
/*   Updated: 2025/03/11 13:38:28 by nseon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMAND_H
# define COMMAND_H

# include <stdint.h>
# include <limits.h>

typedef struct s_cmd
{
	char	path[PATH_MAX];
	char	**args;
	int32_t	args_n;
	char	**env;
	int32_t	env_n;
}	t_cmd;

int	search_path(char *cmd, char cmd_path[PATH_MAX]);
int	exec_cmd(t_cmd *cmd);

#endif
