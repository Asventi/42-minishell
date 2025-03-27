/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nseon <nseon@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 13:56:16 by nseon             #+#    #+#             */
/*   Updated: 2025/03/27 11:22:34 by nseon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

int	is_builtins(char *cmd);
int	launch_builtins(t_cmd *cmd, t_context *ctx);
int	cd_cmd(t_cmd *cmd, t_context *ctx);
int	echo_cmd(t_cmd *cmd);
int	env_cmd(t_context *ctx);
int	pwd_cmd(t_cmd *cmd);
int	exit_cmd(void);
int	export_cmd(t_cmd *cmd, t_context *ctx);
int	unset_cmd(t_cmd *cmd, t_context *ctx);

#endif
