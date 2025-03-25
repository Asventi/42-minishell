/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nseon <nseon@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 11:16:02 by pjarnac           #+#    #+#             */
/*   Updated: 2025/03/25 10:55:49 by nseon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

#include "context.h"
#include "libft.h"
#include "shell/prompt.h"
#include "command.h"
#include "builtins.h"
#include <errno.h>

int	cpy_env(char ***dest, char **env)
{
	int		i;
	char	*res;

	i = 0;
	*dest = vct_create(sizeof (char *), 0);
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
	return (0);
}

int	main(int c, char **args, char **env)
{
	t_context	ctx;

	ft_bzero(&ctx, sizeof (t_context));
	if (cpy_env(&ctx.env, env))
		return (1);
	prompt(&ctx);
}
