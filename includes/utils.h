/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjarnac <pjarnac@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 19:10:38 by pjarnac           #+#    #+#             */
/*   Updated: 2025/03/20 19:10:38 by pjarnac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include <stdint.h>
# include <limits.h>
# include "context.h"

int		search_path(char *cmd, char cmd_path[PATH_MAX], t_context *ctx);
int32_t	close_in_out(int32_t in, int32_t out);
int32_t	create_temp_file(void);
int32_t	open_temp_file(int32_t *tmp_file);

#endif
