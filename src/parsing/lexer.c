/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjarnac <pjarnac@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 13:32:03 by pjarnac           #+#    #+#             */
/*   Updated: 2025/03/19 13:32:03 by pjarnac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

#include "errors.h"
#include "libft.h"
#include "parsing.h"
#include "constants/operators.h"

static void	print_tokens(t_token *tokens)
{
	size_t	i = 0;
	size_t size = vct_size(tokens);

	while (i < size)
	{
		if (tokens[i].type == RIN)
			ft_printf("{token: %-20.20s, %7s}\n", tokens[i].txt, "RIN");
		else if (tokens[i].type == ROUT)
			ft_printf("{token: %-20.20s, %7s}\n", tokens[i].txt, "ROUT");
		else if (tokens[i].type == ROUTAPP)
			ft_printf("{token: %-20.20s, %7s}\n", tokens[i].txt, "ROUTAPP");
		else if (tokens[i].type == HEREDOC)
			ft_printf("{token: %-20.20s, %7s}\n", tokens[i].txt, "HEREDOC");
		else if (tokens[i].type == PIPE)
			ft_printf("{token: %-20.20s, %7s}\n", tokens[i].txt, "PIPE");
		else if (tokens[i].type == NONE)
			ft_printf("{token: %-20.20s, %7s}\n", tokens[i].txt, "NONE");
		else if (tokens[i].type == ARG)
			ft_printf("{token: %-20.20s, %7s}\n", tokens[i].txt, "ARG");
		else if (tokens[i].type == ARGFILE)
			ft_printf("{token: %-20.20s, %7s}\n", tokens[i].txt, "ARGFILE");
		else if (tokens[i].type == COMMAND)
			ft_printf("{token: %-20.20s, %7s}\n", tokens[i].txt, "COMMAND");
		else if (tokens[i].type == INVAL_OP)
			ft_printf("{token: %-20.20s, %7s}\n", tokens[i].txt, "INVALOP");
		else
			ft_printf("{token: %-20.20s, %7s}\n", tokens[i].txt, "WTF");
		i++;
	}
}

void	set_type(t_token *tk, t_type prec)
{
	if (!ft_strcmp(tk->txt, RIN_L))
		tk->type = RIN;
	else if (!ft_strcmp(tk->txt, ROUT_L))
		tk->type = ROUT;
	else if (!ft_strcmp(tk->txt, HEREDOC_L))
		tk->type = HEREDOC;
	else if (!ft_strcmp(tk->txt, ROUTAPP_L))
		tk->type = ROUTAPP;
	else if (!ft_strcmp(tk->txt, PIPE_L))
		tk->type = PIPE;
	else if (prec == NONE || prec == PIPE)
		tk->type = COMMAND;
	else if (ROUT <= prec && prec <= HEREDOC)
		tk->type = ARGFILE;
	else if (!ft_isstrcharset(tk->txt, QUOTES)
		&& ft_isstrcharset(tk->txt, OPERATORS))
		tk->type = INVAL_OP;
	else
		tk->type = ARG;
}

int32_t	lexer(t_token **tokens, char **args)
{
	t_token	tk;

	*tokens = create_vector(sizeof (t_token));
	tk.type = NONE;
	while (*args)
	{
		tk.txt = ft_strdup(*args);
		set_type(&tk, tk.type);
		if (tk.type == INVAL_OP)
			return (p_invalid_op_err(tk.txt), free_vct(*tokens), INVALID_OP);
		vct_add(tokens, &tk);
		args++;
	}
	if (ROUT <= tk.type && tk.type <= PIPE)
		return (p_invalid_op_err(tk.txt), free_vct(*tokens), INVALID_OP);
	return (0);
}
