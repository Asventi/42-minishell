/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nseon <nseon@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 13:56:16 by nseon             #+#    #+#             */
/*   Updated: 2025/04/07 15:07:24 by nseon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "command.h"

int	is_builtins(char *cmd);
int	launch_builtins(t_cmd *cmd, t_context *ctx);
int	cd_cmd(t_cmd *cmd, t_context *ctx);
int	echo_cmd(t_cmd *cmd);
int	env_cmd(t_context *ctx);
int	pwd_cmd(t_context *ctx);
int	exit_cmd(t_cmd *cmd, t_context *ctx);
int	export_cmd(t_cmd *cmd, t_context *ctx);
int	unset_cmd(t_cmd *cmd, t_context *ctx);

#endif
