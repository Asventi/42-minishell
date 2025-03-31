/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nseon <nseon@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 13:49:47 by pjarnac           #+#    #+#             */
/*   Updated: 2025/03/27 14:56:03 by nseon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMAND_H
# define COMMAND_H

# define CHLD_ERR 255
# define CHLD_END 254

# include <limits.h>
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
	int32_t	fd;
}	t_redir;

typedef struct s_cmd
{
	char	path[PATH_MAX];
	t_redir	output;
	t_redir	input;
	char	**args;
}	t_cmd;

int	exec_line(t_cmd *cmd, t_context *ctx);
int	pipex(t_cmd *cmd, t_context *ctx);

#endif
