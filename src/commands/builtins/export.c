/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nseon <nseon@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 14:54:11 by nseon             #+#    #+#             */
/*   Updated: 2025/04/07 17:07:17 by nseon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

#include "command.h"
#include "libft.h"
#include "errors.h"
#include "builtins.h"
#include <stdlib.h>
#include "env.h"

int	check_form(char *tab)
{
	if (!tab)
		return (3);
	while (*tab && *tab != '=')
		tab++;
	if (!*tab)
		return (0);
	if (*tab == '=' && *(tab - 1) == '+')
		return (2);
	return (1);
}

int	is_valid(char *tab)
{
	if (!ft_isalpha(*tab) && *tab != '_')
		return (0);
	while (*tab && *tab != '=')
	{
		if (!ft_isalnum(*tab) && *tab != '_')
			if (!(*tab == '+' && *(tab + 1) == '='))
				return (0);
		tab++;
	}
	return (1);
}

int	remove_var_env(char *env, t_context *ctx)
{
	int		i;
	int		size;

	i = 0;
	while (env[i] && env[i] != '=')
		i++;
	size = i;
	i = 0;
	while (ctx->env[i])
	{
		if (!ft_strncmp(env, ctx->env[i], size)
			&& (ctx->env[i][size] == '\0' || ctx->env[i][size - 1] == '='))
			vct_delete(ctx->env, i);
		i++;
	}
	return (0);
}

int	plus_equal(char *env, t_context *ctx, int i, int size)
{
	char	*content;
	char	*temp;

	while (env[size] && env[size] != '+')
		size++;
	content = ft_strchr(env, '=');
	while (++i >= 0 && ctx->env[i])
	{
		if (!ft_strncmp(env, ctx->env[i], size) && ctx->env[i][size] == '=')
		{
			temp = ft_strjoin(ctx->env[i], content + 1);
			if (!temp)
				return (1);
			free(ctx->env[i]);
			ctx->env[i] = temp;
			i = -2;
		}
	}
	ft_memmove(env + size, env + size + 1, ft_strlen(env + size + 1) + 1);
	if (i >= 0)
		remove_var_env(env, ctx);
	if (i >= 0)
		vct_insert(&ctx->env, &(char *){ft_strdup(env)},
			(int32_t) vct_size(ctx->env) - 1);
	return (0);
}

int	export_cmd(t_cmd *cmd, t_context *ctx)
{
	int	i;

	i = 0;
	if (!cmd->args[1])
		return (print_and_sort(ctx));
	while (cmd->args[i])
	{
		while (cmd->args[++i] && !is_valid(cmd->args[i]))
			p_error("export", cmd->args[i], "not a valid identifier");
		if (check_form(cmd->args[i]) == 1)
		{
			remove_var_env(cmd->args[i], ctx);
			vct_insert(&ctx->env, &(char *){ft_strdup(cmd->args[i])},
				(int32_t) vct_size(ctx->env) - 1);
		}
		if (check_form(cmd->args[i]) == 2)
			if (plus_equal(cmd->args[i], ctx, -1, 0))
				p_error("ft_strjoin", NULL, NULL);
		if (check_form(cmd->args[i]) == 0 && !ft_getenv(cmd->args[i], ctx))
			vct_insert(&ctx->env, &(char *){ft_strdup(cmd->args[i])},
				(int32_t) vct_size(ctx->env) - 1);
	}
	return (0);
}
