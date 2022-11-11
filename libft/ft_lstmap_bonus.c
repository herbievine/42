/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 13:20:16 by herbie            #+#    #+#             */
/*   Updated: 2022/11/11 17:48:43 by herbie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_head;
	t_list	*el;

	if (!lst || !f || !del)
		return (0);
	new_head = ft_lstnew(f(lst->content));
	if (!new_head)
		return (0);
	el = new_head;
	lst = lst->next;
	while (lst)
	{
		el->next = ft_lstnew(f(lst->content));
		if (!el->next)
		{	
			ft_lstclear(&el, del);
			return (0);
		}
		el = el->next;
		lst = lst->next;
	}
	el->next = 0;
	return (new_head);
}
