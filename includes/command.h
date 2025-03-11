/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjarnac <pjarnac@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 13:49:47 by pjarnac           #+#    #+#             */
/*   Updated: 2025/03/06 13:49:47 by pjarnac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMAND_H
# define COMMAND_H

# include <stdint.h>

typedef enum e_operand
{
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
	char			*path;
	char			**args;
	char			**env;
	t_redir
	struct s_cmd	*next;
}	t_cmd;

#endif
