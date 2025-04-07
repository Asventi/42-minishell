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
#include <readline/readline.h>

int32_t	init_signals_child(void)
{
	struct sigaction	sigact;

	sigact = (struct sigaction){0};
	sigact.sa_handler = SIG_DFL;
	if (sigaction(SIGINT, &sigact, 0) == -1)
		return (-1);
	if (sigaction(SIGQUIT, &sigact, 0) == -1)
		return (-1);
	return (0);
}

int32_t	init_signals_exec(void)
{
	struct sigaction	sigact;

	sigact = (struct sigaction){0};
	sigact.sa_handler = sig_exec_handler;
	sigact.sa_flags = SA_RESTART;
	if (sigaction(SIGINT, &sigact, 0) == -1)
		return (-1);
	if (sigaction(SIGQUIT, &sigact, 0) == -1)
		return (-1);
	return (0);
}

int32_t	init_signals_main(void)
{
	struct sigaction	sigact;

	rl_event_hook = rl_hook;
	sigact = (struct sigaction){0};
	sigact.sa_handler = sig_handler;
	sigact.sa_flags = SA_RESTART;
	if (sigaction(SIGINT, &sigact, 0) == -1)
		return (-1);
	sigact.sa_handler = SIG_IGN;
	if (sigaction(SIGQUIT, &sigact, 0) == -1)
		return (-1);
	return (0);
}
