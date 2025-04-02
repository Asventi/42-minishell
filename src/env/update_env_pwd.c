/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_env_pwd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nseon <nseon@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 16:22:06 by nseon             #+#    #+#             */
/*   Updated: 2025/04/02 12:12:07 by nseon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "context.h"
#include "libft.h"
#include "builtins.h"
#include "command.h"
#include <unistd.h>

int update_pwd(t_context *ctx)
{
	char	cmd_line[PATH_MAX + 12];
	char	pwd[PATH_MAX];
	int		res;

	if (!getcwd(pwd, PATH_MAX))
		return (-1);
	ft_strlcpy(cmd_line, "export PWD=", 12);
	ft_strlcat(cmd_line, pwd, PATH_MAX + 4);
	res = process_command(cmd_line, ctx);
	if (res == -1 || res == CHLD_END || res == CHLD_ERR)
		return (res);
	return (0);
}

int update_oldpwd(t_context *ctx, char *oldpwd)
{
	char	cmd_line[PATH_MAX + 15];
	int		res;

	ft_strlcpy(cmd_line, "export OLDPWD=", 15);
	ft_strlcat(cmd_line, oldpwd, PATH_MAX + 4);
	res = process_command(cmd_line, ctx);
	if (res == -1 || res == CHLD_END || res == CHLD_ERR)
		return (res);
	return (0);
}
