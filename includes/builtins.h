/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nseon <nseon@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 13:56:16 by nseon             #+#    #+#             */
/*   Updated: 2025/03/21 09:36:21 by nseon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

int	cd_cmd(t_cmd *cmd);
int	echo_cmd(t_cmd *cmd);
int	pwd_cmd(t_cmd *cmd);

#endif
