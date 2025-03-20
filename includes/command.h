/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nseon <nseon@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 13:49:47 by pjarnac           #+#    #+#             */
/*   Updated: 2025/03/20 16:34:45 by nseon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMAND_H
# define COMMAND_H

# include <stdint.h>
# include <limits.h>

// ROUT = > fichier
// RIN = < fichier
// ROUTAPP = >> fichier
// HEREDOC = << delimiter

typedef enum e_operand
{
	NONE,
	ROUT,
	RIN,
	ROUTAPP,
	HEREDOC
}	t_operand;

typedef struct s_redir
{
	t_operand	op;
	char		*path;
}	t_redir;

typedef struct s_cmd
{
	char	path[PATH_MAX];
	t_redir	output;
	t_redir	input;
	char	**args;
	int32_t	nb_args;
	char	**env;
}	t_cmd;

int	search_path(char *cmd, char cmd_path[PATH_MAX]);
int	exec_cmd(t_cmd *cmd);

#endif
