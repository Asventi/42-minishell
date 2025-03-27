/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nseon <nseon@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 08:40:45 by nseon             #+#    #+#             */
/*   Updated: 2025/03/27 09:45:40 by nseon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.h"
#include "redirect.h"

int	check_op(t_cmd *cmd)
{
	if (cmd->input.op == RIN)
		if (rin(cmd))
			return (-1);
	if (cmd->input.op == HEREDOC)
		if (heredoc(cmd))
			return (-1);
	if (cmd->output.op == ROUT)
		if (rout(cmd))
			return (-1);
	if (cmd->output.op == ROUTAPP)
		if (routapp(cmd))
			return (-1);
	return (0);
}
