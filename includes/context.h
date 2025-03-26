/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   context.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjarnac <pjarnac@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 14:41:58 by pjarnac           #+#    #+#             */
/*   Updated: 2025/03/06 14:41:58 by pjarnac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONTEXT_H
# define CONTEXT_H

# include <limits.h>
# include <stdint.h>

typedef struct s_context
{
	char	path[PATH_MAX];
	char	**env;
	char	*tty;
	int32_t	last_code;
}	t_context;

#endif
