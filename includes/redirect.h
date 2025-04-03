/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nseon <nseon@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 10:28:31 by nseon             #+#    #+#             */
/*   Updated: 2025/04/03 14:44:55 by nseon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REDIRECT_H
# define REDIRECT_H

# define TMP_HEREDOC "/tmp/heredoc_minishell"
# define BROWN "\001\x1b[33m\002"
# define RESET "\001\x1b[0m\002"
# define HEREDOC_WARN "bash: warning: here-document delimited by end-of-file (wanted `%s')\n"

# include "command.h"

int		check_op(t_cmd *cmd);
int32_t	heredoc(char *deli);
int		rin(t_cmd *cmd);
int		rout(t_cmd *cmd);
int		routapp(t_cmd *cmd);

#endif
