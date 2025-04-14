/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjarnac <pjarnac@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 14:39:40 by pjarnac           #+#    #+#             */
/*   Updated: 2025/03/28 14:39:40 by pjarnac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_H
# define SIGNALS_H

# include <stdint.h>

int32_t	init_signals_main(void);
int32_t	init_signals_exec(void);
int32_t	init_signals_child(void);
int32_t	rl_hook(void);
void	sig_handler(int sig);
void	sig_exec_handler(int sig);
int32_t	init_signals_builtins(void);

#endif
