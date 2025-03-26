/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nseon <nseon@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 13:49:47 by pjarnac           #+#    #+#             */
/*   Updated: 2025/03/26 11:00:45 by nseon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMAND_H
# define COMMAND_H

# include <stdint.h>
# include <limits.h>
# include "context.h"

# include "context.h"

// ROUT = > fichier
// RIN = < fichier
// ROUTAPP = >> fichier
// HEREDOC = << delimiter

typedef enum e_type
{
	NONE,
	ROUT,
	ROUTAPP,
	RIN,
	HEREDOC,
	PIPE,
	ARG,
	ARGFILE,
	COMMAND,
	INVAL_OP,
}	t_type;

typedef struct s_redir
{
	t_type	op;
	char	path[PATH_MAX];
}	t_redir;

typedef struct s_cmd
{
	char	path[PATH_MAX];
	t_redir	output;
	t_redir	input;
	char	**args;
}	t_cmd;

int	search_path(char *cmd, char cmd_path[PATH_MAX], t_context *ctx);
int	exec_cmd(t_cmd *cmd, t_context *ctx);

#endif
