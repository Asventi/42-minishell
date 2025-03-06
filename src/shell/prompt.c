/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjarnac <pjarnac@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 13:41:23 by pjarnac           #+#    #+#             */
/*   Updated: 2025/03/06 13:41:23 by pjarnac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <stdint.h>
#include <stdio.h>
#include <unistd.h>
#include <readline/readline.h>
#include "context.h"
#include "libft.h"
#include "shell/prompt.h"

static void	get_prompt(char str[PATH_MAX + 16], t_context *ctx)
{
	size_t	i;

	i = 0;
	i += ft_strlcpy(str + i, "\n\n" CYAN, PATH_MAX + 16);
	i += ft_strlcpy(str + i, ctx->path, PATH_MAX + 16);
	if (ctx->last_code != 0)
		i += ft_strlcpy(str + i, RESET RED "\n❯ " RESET, PATH_MAX + 16);
	else
		i += ft_strlcpy(str + i, RESET GREEN "\n❯ " RESET, PATH_MAX + 16);
	str[i + 1] = 0x27;
	str[i + 2] = 0;
}

int	prompt(t_context *ctx)
{
	char	ptext[PATH_MAX + 16];

	getcwd(ctx->path, PATH_MAX);
	while (1)
	{
		errno = 0;
		get_prompt(ptext, ctx);
		printf("%s", readline(ptext));
		if (ctx->last_code == 0)
			ctx->last_code = 1;
		else
			ctx->last_code = 0;
	}
	return (0);
}
