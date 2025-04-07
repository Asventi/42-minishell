/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nseon <nseon@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 09:30:31 by nseon             #+#    #+#             */
/*   Updated: 2025/04/07 15:07:05 by nseon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.h"
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <context.h>

int	pwd_cmd(t_context *ctx)
{
	printf("%s\n", ctx->path);
	return (0);
}
