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

#include "context.h"
#include "libft.h"
#include "shell/prompt.h"
#include "parsing.h"

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
