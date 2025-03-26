/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nseon <nseon@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 11:16:02 by pjarnac           #+#    #+#             */
/*   Updated: 2025/03/25 16:55:26 by nseon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <signal.h>
#include <readline/readline.h>

#include "context.h"
#include "libft.h"
#include "shell/prompt.h"
#include "parsing.h"

int	g_sig = 0;

void	sig_handler(int sig)
{
	g_sig = sig;
	if (sig == SIGINT)
	{
		rl_replace_line("", 0);
		rl_forced_update_display();
	}
}

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

static int32_t	init_signals(void)
{
	struct sigaction	sigact;

	sigact = (struct sigaction){0};
	sigact.sa_handler = sig_handler;
	sigact.sa_flags = SA_RESTART | SA_NOCLDSTOP;
	if (sigaction(SIGINT, &sigact, 0) == -1)
		return (-1);
	if (sigaction(SIGQUIT, &sigact, 0) == -1)
		return (-1);
	return (0);
}

int	main(int c, char **args, char **env)
{
	t_context	ctx;
	int32_t		res;

	(void)c;
	(void)args;
	if (init_signals() == -1)
		return (EXIT_FAILURE);
	ft_bzero(&ctx, sizeof (t_context));
	if (cpy_env(&ctx.env, env))
		return (1);
	res = prompt(&ctx);
	vct_destroy(ctx.env);
	if (res == CHLD_ERR)
		return (CHLD_ERR);
	if (res == -1)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
