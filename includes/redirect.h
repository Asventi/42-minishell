/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nseon <nseon@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 10:28:31 by nseon             #+#    #+#             */
/*   Updated: 2025/03/27 11:13:51 by nseon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REDIRECT_H
# define REDIRECT_H

# define BUF_SIZE 500000

# include "command.h"

int	check_op(t_cmd *cmd, int *pipefd);
int	heredoc(t_cmd *cmd, int pipefd[2]);
int	rin(t_cmd *cmd);
int	rout(t_cmd *cmd);
int	routapp(t_cmd *cmd);

#endif
