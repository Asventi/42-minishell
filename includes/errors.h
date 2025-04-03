/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nseon <nseon@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 14:51:08 by pjarnac           #+#    #+#             */
/*   Updated: 2025/04/02 16:14:27 by nseon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERRORS_H
# define ERRORS_H

# define MINISHELL "minishell: "
# define BASE_ERROR "%s: %s"
# define BASE_ERR_RES "%s: %s: %s"
# define CMD_NOT_FOUND "%s: command not found"
# define SYNTAX_ERROR "syntax error near unexpected token `%c'"
# define INVALID_OP_ERROR "invalid operator: %s"
# define SYNTAX_ERROR_NL "syntax error near unexpected token `newline'"
# define ERR_F 2
# define FATAL -1
# define EXIT 2048

int		p_error(const char *src, const char *reason, const char *msg);
void	p_errorexit(const char *src, const char *reason, const char *msg);
int		p_syntax_error(char c);
int		p_invalid_op_err(char *str);

#endif
