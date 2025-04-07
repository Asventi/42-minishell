/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_env_pwd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nseon <nseon@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 16:22:06 by nseon             #+#    #+#             */
/*   Updated: 2025/04/07 16:26:57 by nseon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "context.h"
#include "libft.h"
#include "command.h"
#include <unistd.h>
#include "env.h"
#include "errors.h"

int	update_oldpwd(t_context *ctx)
{
	char	cmd_line[PATH_MAX + 15];
	int		res;
	char	*pwd;

	pwd = ft_getenv("PWD", ctx);
	if (!pwd)
		return (1);
	ft_strlcpy(cmd_line, "export OLDPWD=", 15);
	ft_strlcat(cmd_line, pwd, PATH_MAX + 4);
	res = process_command(cmd_line, ctx);
	if (res == -1 || res == CHLD_END)
		return (res);
	return (0);
}

int	update_pwd(t_context *ctx, char *arg)
{
	char	cmd_line[PATH_MAX + 12];
	char	pwd[PATH_MAX];
	int		res;

	res = update_oldpwd(ctx);
	if (res)
		return (res);
	if (!getcwd(pwd, PATH_MAX))
	{
		p_error("getcwd", NULL, NULL);
		ft_strlcat(ctx->path, "/", PATH_MAX);
		if (arg[ft_strlen(arg) - 1] == '/')
			arg[ft_strlen(arg) - 1] = '\0';
		ft_strlcat(ctx->path, arg, PATH_MAX);
	}
	else
		ft_strlcpy(ctx->path, pwd, PATH_MAX);
	ft_strlcpy(cmd_line, "export PWD=", 12);
	ft_strlcat(cmd_line, ctx->path, PATH_MAX + 4);
	res = process_command(cmd_line, ctx);
	if (res == -1 || res == CHLD_END)
		return (res);
	return (0);
}
