/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 13:20:16 by herbie            #+#    #+#             */
/*   Updated: 2023/05/21 11:53:40 by herbie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief The ft_lstmap funtion iterates the list 'lst' and applies the
 * function 'f' to the content of each node. Creates a new list resulting of the
 * successive applications of the function 'f'. The 'del' function is used to
 * delete the content of a node if needed.
 * 
 * @param lst 
 * @param f 
 * @param del 
 * @return t_list* 
 */
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
