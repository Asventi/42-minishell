/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjarnac <pjarnac@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 14:51:08 by pjarnac           #+#    #+#             */
/*   Updated: 2025/03/12 14:51:08 by pjarnac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERRORS_H
# define ERRORS_H

# define MINISHELL "minishell"
# define CMD_NOT_FOUND "command not found\n"
# define SEP ": "

int		p_cmd_not_found(const char *src);
int		p_error(const char *src);
void	p_errorexit(const char *src);

#endif
