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

int	p_cmd_not_found(const char *src)
{
	ft_fprintf(ERR_F, CMD_NOT_FOUND, src);
	return (-1);
}

int	p_error(const char *src)
{
	char	*err;

	err = strerror(errno);
	ft_fprintf(ERR_F, MINISHELL BASE_ERROR, src, err);
	return (-1);
}

void	p_errorexit(const char *src)
{
	p_error(src);
	exit(EXIT_FAILURE);
}
