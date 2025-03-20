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

# define MINISHELL "minishell: "
# define BASE_ERROR "%s: %s\n"
# define CMD_NOT_FOUND "%s: command not found\n"
# define SYNTAX_ERROR "syntax error near unexpected token `%c'\n"
# define SYNTAX_ERROR_NL "syntax error near unexpected token `newline'\n"
# define ERR_F 2

int		p_cmd_not_found(const char *src);
int		p_error(const char *src);
void	p_errorexit(const char *src);
int		p_syntax_error(char c);

#endif
