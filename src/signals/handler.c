/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjarnac <pjarnac@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 13:09:25 by pjarnac           #+#    #+#             */
/*   Updated: 2025/04/07 13:09:25 by pjarnac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "signals.h"
#include <signal.h>
#include <readline/readline.h>

extern int32_t	g_sig;

void	sig_handler(int sig)
{
	g_sig = sig;
	if (sig == SIGINT)
	{
		rl_line_buffer[0] = 0;
		rl_done = 1;
	}
}

void	sig_exec_handler(int sig)
{
	g_sig = sig;
}

int32_t	rl_hook(void)
{
	return (0);
}
