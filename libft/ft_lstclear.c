/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 12:30:27 by herbie            #+#    #+#             */
/*   Updated: 2022/11/10 12:41:58 by herbie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list *head;
	t_list *tmp;
	
	if (!lst || !del)
		return;
	head = *lst;
	while (head)
	{
		tmp = head;
		ft_lstdelone(head, del);
		head = tmp->next;
	}

	*lst = 0;
}