/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nseon <nseon@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 11:16:02 by pjarnac           #+#    #+#             */
/*   Updated: 2025/03/11 11:15:27 by nseon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

#include "context.h"
#include "libft.h"
#include "shell/prompt.h"
#include "command.h"

int	main(int c, char **args, char **env)
{
	t_context	ctx;
	char cmd_path[PATH_MAX];

	ft_bzero(&ctx, sizeof (t_context));
	search_path(args[1], cmd_path);
	ft_printf("%s\n", cmd_path);
	ctx.env = env;
	prompt(&ctx);
}
