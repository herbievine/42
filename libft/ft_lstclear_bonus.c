/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 12:30:27 by herbie            #+#    #+#             */
/*   Updated: 2022/11/11 21:16:33 by herbie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief The ft_lstclear() function deletes and frees the given node and every
 * successor of that node, using the function 'del' and free(3).
 * 
 * @param lst 
 * @param del 
 */
void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*head;
	t_list	*tmp;

	if (!lst || !del)
		return ;
	head = *lst;
	while (head)
	{
		tmp = head->next;
		ft_lstdelone(head, del);
		head = tmp;
	}
	*lst = 0;
}
