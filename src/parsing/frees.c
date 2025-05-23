/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frees.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjarnac <pjarnac@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 13:25:23 by pjarnac           #+#    #+#             */
/*   Updated: 2025/03/25 13:25:23 by pjarnac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>

#include "parsing.h"
#include "libft.h"

void	free_args(void *p)
{
	char	*str;

	str = *(char **)p;
	free(str);
}

void	free_cmds(void *p)
{
	t_cmd	*cmd;

	cmd = (t_cmd *)p;
	if (cmd->input.fd != NONE && cmd->input.fd > 0)
		close(cmd->input.fd);
	if (cmd->output.fd != NONE && cmd->output.fd > 0)
		close(cmd->output.fd);
	if (cmd->args)
		vct_destroy(cmd->args);
}

void	free_token(void *p)
{
	const t_token	*tk = (t_token *)p;

	free_vct(tk->txt);
}

void	free_tokenexp(void *p)
{
	const t_token	*tk = (t_token *)p;

	if (tk->txt)
		vct_destroy(tk->txt);
}

void	free_env(void *p)
{
	char	*str;

	str = *(char **)p;
	if (str)
		free(str);
}
