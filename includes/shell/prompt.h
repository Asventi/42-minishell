/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjarnac <pjarnac@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 13:41:36 by pjarnac           #+#    #+#             */
/*   Updated: 2025/03/06 13:41:36 by pjarnac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROMPT_H
# define PROMPT_H

# define RED "\x1b[31m"
# define GREEN "\x1b[32m"
# define CYAN "\x1b[36m"
# define RESET "\x1b[0m"

# include "context.h"

int	prompt(t_context *ctx);

#endif
