/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nseon <nseon@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 14:33:37 by pjarnac           #+#    #+#             */
/*   Updated: 2025/03/21 11:28:56 by nseon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# define INVALID_OP 1
# define INVALID_FILE 2

# include "context.h"
# include "command.h"

typedef struct s_token
{
	char	*txt;
	t_type	type;
}	t_token;

int32_t	parse(char *str, t_cmd **cmd, t_context *ctx);
int32_t	tokenize(char ***args, char *str);
int32_t	lexer(t_token **tokens, char **args);
int32_t	expander(t_token **tokens_exp, t_token *tokens, t_context *ctx);

void	free_cmds(void *p);
void	free_args(void *p);
void	free_token(void *p);
void	free_tokenexp(void *p);
void	free_env(void *p);

#endif
