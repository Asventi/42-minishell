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
#include <stdlib.h>

#include "errors.h"
#include "libft.h"
#include "parsing.h"
#include "constants/operators.h"

static bool	is_command(t_token	*tklist)
{
	const int32_t	size = (int32_t)vct_size(tklist);
	int32_t			i;
	int32_t			total;

	i = 0;
	total = 0;
	while (i < size)
	{
		if (tklist[i].type == COMMAND)
			total++;
		if (tklist[i].type == PIPE)
			total--;
		i++;
	}
	return (total == 0);
}

static void	set_type(t_token *tklist, t_token *tk, t_type prec)
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
	else if (ROUT <= prec && prec <= HEREDOC)
		tk->type = ARGFILE;
	else if (is_command(tklist))
		tk->type = COMMAND;
	else if (!ft_isstrcharset(tk->txt, QUOTES)
		&& ft_isstrcharset(tk->txt, OPERATORS))
		tk->type = INVAL_OP;
	else
		tk->type = ARG;
}

static int32_t	process_quotes(t_token *tk)
{
	int32_t	i;
	int32_t	quote;

	i = -1;
	quote = 0;
	while (++i < (int32_t)vct_size(tk->txt))
	{
		if (!quote && ft_ischarset(tk->txt[i], QUOTES))
		{
			quote = (int32_t)tk->txt[i];
			vct_delete(tk->txt, i);
		}
		else if (quote && quote == tk->txt[i])
		{
			quote = 0;
			vct_delete(tk->txt, i);
		}
	}
	return (0);
}

static int32_t	dup_arg(t_token *tk, char *str)
{
	tk->txt = vct_create(sizeof (char), 0, DESTROY_ON_FAIL);
	if (!tk->txt)
		return (FATAL);
	if (vct_strcpy(&tk->txt, str) == -1)
		return (FATAL);
	if (ft_isstrcharset(tk->txt, QUOTES))
		tk->quoted = true;
	else
		tk->quoted = false;
	return (0);
}

int32_t	lexer(t_token **tokens, char **args)
{
	t_token	tk;

	*tokens = vct_create(sizeof (t_token), free_token, DESTROY_ON_FAIL);
	if (!*tokens)
		return (-1);
	tk.type = NONE;
	while (*args)
	{
		if (dup_arg(&tk, *args) == -1)
			return (vct_destroy(*tokens), FATAL);
		set_type(*tokens, &tk, tk.type);
		if (tk.type == INVAL_OP)
			return (p_invalid_op_err(tk.txt), vct_destroy(*tokens), INVALID_OP);
		process_quotes(&tk);
		if (vct_add(tokens, &tk) != 0)
			return (-1);
		args++;
	}
	if (ROUT <= tk.type && tk.type <= PIPE)
		return (p_invalid_op_err(tk.txt), vct_destroy(*tokens), INVALID_OP);
	return (0);
}
