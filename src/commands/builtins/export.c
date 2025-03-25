/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nseon <nseon@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 14:54:11 by nseon             #+#    #+#             */
/*   Updated: 2025/03/25 16:59:08 by nseon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.h"
#include "libft.h"
#include "errors.h"
#include "builtins.h"
#include <stdlib.h>
#include <errno.h>

int	check_form(char *tab)
{
	if (!tab)
		return (0);
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
	if (!ft_isalpha(*tab))
		return (0);
	while (*tab && *tab != '=')
	{
		if (!ft_isalnum(*tab))
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
		if (!ft_strncmp(env, ctx->env[i], size))
			if (ctx->env[i][size] == '=')
				vct_delete(ctx->env, i);
		i++;
	}
	return (0);
}

int	plus_equal(char *env, t_context *ctx, int i)
{
	char	*content;
	char	*temp;
	int		size;

	size = 0;
	while (env[size] && env[size] != '+')
		size++;
	content = ft_strchr(env, '=');
	while (++i >= 0 && ctx->env[i])
	{
		if (!ft_strncmp(env, ctx->env[i], size))
			if (ctx->env[i][size] == '=')
			{
				temp = ft_strjoin(ctx->env[i], content + 1);
				if (!temp)
					return (1);
				ctx->env[i] = temp;
				i = -2;
			}
	}
	ft_strlcpy(env, env, size + 1);
	ft_strlcat(env, content, ft_strlen(env) + ft_strlen(content) + 1);
	if (i >= 0)
		vct_insert(&ctx->env, &env, vct_size(ctx->env) - 1);
	return (0);
}

int	export_cmd(t_cmd *cmd, t_context *ctx)
{
	int	i;
	int	j;

	i = 0;
	while (cmd->args[i])
	{
		j = 0;
		while (cmd->args[++i] && !is_valid(cmd->args[i]))
			p_error("export", cmd->args[i], "not a valid identifier");
		if (check_form(cmd->args[i]))
		{
			if (check_form(cmd->args[i]) == 1)
			{
				remove_var_env(cmd->args[i], ctx);
				vct_insert(&ctx->env, &cmd->args[i], vct_size(ctx->env) - 1);
			}
			if (check_form(cmd->args[i]) == 2)
				if (plus_equal(cmd->args[i], ctx, -1))
					p_error("ft_strjoin", NULL, NULL);
		}
	}
	return (0);
}
