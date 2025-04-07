/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjarnac <pjarnac@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 12:14:07 by pjarnac           #+#    #+#             */
/*   Updated: 2024/11/12 15:57:47 by pjarnac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*node;
	t_list	*next;

	if (!f || !del)
		return (NULL);
	node = NULL;
	if (lst)
	{
		node = ft_lstnew(0);
		if (!node)
			return (NULL);
		node->content = f(lst->content);
		next = ft_lstmap(lst->next, f, del);
		if (!next && lst->next)
		{
			ft_lstdelone(node, del);
			return (NULL);
		}
		node->next = next;
	}
	return (node);
}
