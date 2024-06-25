/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: databey <databey@student.42kocaeli.com.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 02:47:53 by databey           #+#    #+#             */
/*   Updated: 2023/10/21 16:15:13 by databey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_list;
	t_list	*save;
	void	*content;

	if (!lst || !f || !del)
		return (0);
	save = 0;
	while (lst)
	{
		content = f(lst->content);
		new_list = ft_lstnew(content);
		if (!new_list)
		{
			del(content);
			ft_lstclear(&save, del);
			return (0);
		}
		ft_lstadd_back(&save, new_list);
		lst = lst->next;
	}
	new_list->next = NULL;
	return (save);
}
