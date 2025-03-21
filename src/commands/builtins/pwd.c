/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nseon <nseon@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 09:30:31 by nseon             #+#    #+#             */
/*   Updated: 2025/03/21 09:38:13 by nseon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "command.h"
#include <unistd.h>
#include <limits.h>
#include <stdio.h>
#include <errno.h>

int	pwd_cmd(t_cmd *cmd)
{
	char	*path;

	if (!getcwd(path, PATH_MAX))
		return (errno);
	printf("%s\n", path);
	return (0);
}
