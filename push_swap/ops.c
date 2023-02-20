/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ops.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 14:58:05 by herbie            #+#    #+#             */
/*   Updated: 2023/02/20 17:54:38 by herbie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "display.h"
#include "ops.h"
#include <stdio.h>

/**
 * @brief The ft_rotate() function rotates the stack, moving all elements up by
 * one, and the last element becomes the first.
 *
 * @param lst
 */
void	ft_rotate(t_list **list, char *op)
{
	t_list	*last;
	t_list	*tmp;

	last = ft_lstlast(*list);
	tmp = ft_lstnew((*list)->content);
	last->next = tmp;
	*list = (*list)->next;
	ft_putstr_fd(op, 1);
}

/**
 * @brief The ft_push() function moves the first element of the stack to the top
 * of the other stack.
 * 
 * @param src 
 * @param dst 
 */
void	ft_push(t_list **src, t_list **dst, char *op)
{
	t_list	*tmp;

	tmp = ft_lstnew((*src)->content);
	if (!*dst)
		*dst = ft_lstnew((*src)->content);
	else
		ft_lstadd_front(dst, tmp);
	*src = (*src)->next;
	ft_putstr_fd(op, 1);
}
