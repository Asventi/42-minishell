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

int32_t	check_file_create(char *str);
int		search_path(char *cmd, char cmd_path[PATH_MAX], t_context *ctx);
int32_t	reset_stds(t_context *ctx);
int32_t	close_pipe(int32_t in, int32_t out);

#endif
