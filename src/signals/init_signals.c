/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_signals.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjarnac <pjarnac@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 18:10:07 by pjarnac           #+#    #+#             */
/*   Updated: 2025/03/26 18:10:07 by pjarnac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "signals.h"

#include <signal.h>
#include <stdio.h>
#include <readline/readline.h>

extern int32_t	g_sig;

void	sig_handler(int sig)
{
	g_sig = sig;
	if (sig == SIGINT)
	{
		printf("\n");
		rl_replace_line("", 0);
		rl_forced_update_display();
	}
}

int32_t	init_signals(void)
{
	struct sigaction	sigact;

	sigact = (struct sigaction){0};
	sigact.sa_handler = sig_handler;
	sigact.sa_flags = SA_NOCLDSTOP;
	if (sigaction(SIGINT, &sigact, 0) == -1)
		return (-1);
	sigact.sa_handler = SIG_IGN;
	if (sigaction(SIGQUIT, &sigact, 0) == -1)
		return (-1);
	return (0);
}
