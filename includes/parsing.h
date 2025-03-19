/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjarnac <pjarnac@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 14:33:37 by pjarnac           #+#    #+#             */
/*   Updated: 2025/03/10 14:33:37 by pjarnac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# define OPERATORS "<>|\\&!"
# define QUOTES "\"\'"

# include "context.h"
# include "command.h"

int		parse(char *str, t_cmd *cmd, t_context *ctx);
char	**tokenize(char *str);

#endif
