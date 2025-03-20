/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjarnac <pjarnac@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 14:33:43 by pjarnac           #+#    #+#             */
/*   Updated: 2025/03/10 14:33:43 by pjarnac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <errno.h>

#include "context.h"
#include "command.h"
#include "parsing.h"
#include "libft.h"
#include "errors.h"

int	parse(char *str, t_cmd *cmd, t_context *ctx)
{
	char	**args;

	args = tokenize(str);
	return (0);
}
