/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nseon <nseon@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 14:54:11 by nseon             #+#    #+#             */
/*   Updated: 2025/03/25 10:20:34 by nseon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.h"
#include "libft.h"
#include "errors.h"

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
				vct_add(&ctx->env, &cmd->args[i]);
			if (check_form(cmd->args[i] == 2))
				
		}
	}
	return (0);
}
