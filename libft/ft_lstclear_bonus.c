/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 12:30:27 by herbie            #+#    #+#             */
/*   Updated: 2022/11/11 15:56:43 by herbie           ###   ########.fr       */
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
		tmp = head->next;
		ft_lstdelone(head, del);
		head = tmp;
	}

	*lst = 0;
}