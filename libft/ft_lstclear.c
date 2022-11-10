/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvine <hvine@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 12:30:27 by herbie            #+#    #+#             */
/*   Updated: 2022/11/10 14:47:32 by hvine            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*head;
	t_list	*tmp;

	if (!lst || !del)
		return ;
	head = *lst;
	while (head)
	{
		tmp = head;
		ft_lstdelone(head, del);
		head = tmp->next;
	}
	*lst = 0;
}
