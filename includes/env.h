/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nseon <nseon@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 17:49:10 by pjarnac           #+#    #+#             */
/*   Updated: 2025/04/07 16:13:09 by nseon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

# include "context.h"

int		check_form(char *tab);
char	*ft_getenv(char *name, t_context *ctx);
char	*ft_getenv_trim(char *name, t_context *ctx);
void	sort(char **tab, int first, int last);
int		print_and_sort(t_context *ctx);
int		update_pwd(t_context *ctx, char *arg);
int		update_oldpwd(t_context *ctx);
int32_t	expand_envvar_quote(char **res, char *envname, t_context *ctx);
int32_t	expand_envvar_trim(char **res, char *envname, t_context *ctx);
int32_t	expand_last_code(char **res, t_context *ctx);
;
#endif
