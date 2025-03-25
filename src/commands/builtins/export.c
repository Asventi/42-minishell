/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nseon <nseon@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 14:54:11 by nseon             #+#    #+#             */
/*   Updated: 2025/03/24 16:36:33 by nseon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.h"
#include "libft.h"

int	is_good(char *str)
{

	if (!ft_isalpha(*str))
		return (0);
	while (*str && *str != '=' && *str != '+')
	{
		if (!ft_isalnum(*str))
			return (0);
		str++;
	}
	if (*str == '=')
		return (1);
	if (*str == '+' && *str + 1 == '=')
		return (2);
	return (0);
}

int	add_previous_env(t_context ctx, char **tab)
{}

int	add_var_env(t_cmd *cmd, t_context *ctx, int i)
{
	char	*tab;

	if (is_good(cmd->args[i]) == 2)
	{

	}
	vct_add(&ctx->env, &cmd->args[i]);
}

int	export_cmd(t_cmd *cmd, t_context *ctx)
{
	int	i;

	i = 1;
	while (cmd->args[i])
	{
		while (!is_good(cmd->args[i]))
			i++;
		add_var_env(cmd, ctx, i);
		i++;
	}
	return (0);
}
