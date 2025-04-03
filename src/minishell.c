/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nseon <nseon@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 11:16:02 by pjarnac           #+#    #+#             */
/*   Updated: 2025/04/03 13:04:38 by nseon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <readline/readline.h>
#include "context.h"
#include "libft.h"
#include "shell/prompt.h"
#include "parsing.h"
#include "signals.h"
#include "errors.h"

int	g_sig;

int	cpy_env(char ***dest, char **env)
{
	int		i;
	char	*res;

	i = 0;
	*dest = vct_create(sizeof (char *), free_env, 0);
	if (!*dest)
		return (errno);
	while (env[i])
	{
		res = ft_strdup(env[i]);
		if (!res)
			return (errno);
		vct_add(dest, &res);
		i++;
	}
	vct_add(dest, &(char *){0});
	return (0);
}

int	main(int c, char **args, char **env)
{
	t_context	ctx;
	int32_t		res;

	(void)c;
	(void)args;
	if (!isatty(0) || !isatty(1))
	{
		ft_fprintf(2, "Is not a tty\n");
		return (EXIT_SUCCESS);
	}
	if (init_signals_main() == -1)
		return (EXIT_FAILURE);
	ft_bzero(&ctx, sizeof (t_context));
	if (cpy_env(&ctx.env, env))
		return (1);
	ctx.tty = ttyname(1);
	res = prompt(&ctx);
	vct_destroy(ctx.env);
	if (res == EXIT)
		return (ctx.last_code);
	if (res == -1 || res == CHLD_ERR)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
