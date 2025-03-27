/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nseon <nseon@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 09:40:00 by nseon             #+#    #+#             */
/*   Updated: 2025/03/27 09:47:12 by nseon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.h"
#include <errno.h>
#include "redirect.h"
#include "shell/prompt.h"
#include "libft.h"
#include "unistd.h"

int	heredoc(t_cmd *cmd, int pipefd[2])
{
	char	buf[BUF_SIZE];
	char	input[BUF_SIZE];
	int		nb_read;

	nb_read = 1;
	ft_bzero(input, BUF_SIZE);
	while (nb_read)
	{
		write (1, BROWN "> " RESET, ft_strlen(BROWN "> " RESET));
		ft_bzero(buf, BUF_SIZE);
		nb_read = (int32_t)read(0, buf, BUF_SIZE);
		if (nb_read == -1)
			return (errno);
		if (nb_read - 1 == (int32_t) ft_strlen(cmd->input.path)
			&& !ft_strncmp(buf, cmd->input.path, nb_read - 1))
			break ;
		if (nb_read)
			ft_strlcat(input, buf, BUF_SIZE);
	}
	if (pipe(pipefd) == -1)
		return (errno);
	write(pipefd[1], input, ft_strlen(input));
	close(pipefd[1]);
	dup2(pipefd[0], 0);
	return (0);
}
