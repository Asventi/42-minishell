/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nseon <nseon@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 13:41:36 by pjarnac           #+#    #+#             */
/*   Updated: 2025/03/17 13:20:02 by nseon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROMPT_H
# define PROMPT_H

# define BROWN "\001\x1b[33m\002"
# define RED "\001\x1b[31m\002"
# define GREEN "\001\x1b[32m\002"
# define CYAN "\001\x1b[36m\002"
# define RESET "\001\x1b[0m\002"

# define RED_PROMPT "\001\x1b[31m\002\n-> \001\x1b[0m\002"
# define GREEN_PROMPT "\001\x1b[32m\002\n-> \001\x1b[0m\002"

# include "context.h"

int	prompt(t_context *ctx);

#endif
