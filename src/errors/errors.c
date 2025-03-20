/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjarnac <pjarnac@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 14:47:03 by pjarnac           #+#    #+#             */
/*   Updated: 2025/03/12 14:47:03 by pjarnac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

#include "libft.h"
#include "errors.h"

int	p_syntax_error(char c)
{
	if (c == 0)
		ft_fprintf(ERR_F, MINISHELL SYNTAX_ERROR_NL);
	else
		ft_fprintf(ERR_F, MINISHELL SYNTAX_ERROR, c);
	return (-1);
}

int	p_invalid_op_err(char *str)
{
	ft_fprintf(ERR_F, MINISHELL INVALID_OP_ERROR, str);
	return (-1);
}

int	p_error(const char *src, const char *reason, const char *msg)
{
	char	*err;

	err = strerror(errno);
	if (!reason)
	{
		if (!msg)
			ft_fprintf(ERR_F, MINISHELL BASE_ERROR "\n", src, err);
		else
			ft_fprintf(ERR_F, MINISHELL BASE_ERROR "\n", src, msg);
	}
	else
	{
		if (!msg)
			ft_fprintf(ERR_F, MINISHELL BASE_ERR_RES "\n", src, reason, err);
		else
			ft_fprintf(ERR_F, MINISHELL BASE_ERR_RES "\n", src, reason, msg);
	}
	return (-1);
}

void	p_errorexit(const char *src, const char *reason, const char *msg)
{
	p_error(src, reason, msg);
	exit(EXIT_FAILURE);
}
