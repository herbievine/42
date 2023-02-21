/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ops.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 14:58:05 by herbie            #+#    #+#             */
/*   Updated: 2023/02/21 08:33:36 by herbie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "display.h"
#include "ops.h"

/**
 * @brief The ft_rotate() function rotates the stack, moving all elements up by
 * one, and the first element becomes the last.
 *
 * @param lst
 * @param op
 */
void	ft_rotate(t_list **list, char *op)
{
	t_list	*last;
	t_list	*tmp;

	last = ft_lstlast(*list);
	tmp = ft_lstnew((*list)->v);
	last->n = tmp;
	*list = (*list)->n;
	ft_putstr_fd(op, 1);
}

/**
 * @brief The ft_push() function moves the first element of the stack to the top
 * of the other stack.
 * 
 * @param src 
 * @param dst 
 * @param op
 */
void	ft_push(t_list **src, t_list **dst, char *op)
{
	t_list	*tmp;

	tmp = ft_lstnew((*src)->v);
	if (!*dst)
		*dst = ft_lstnew((*src)->v);
	else
		ft_lstadd_front(dst, tmp);
	*src = (*src)->n;
	ft_putstr_fd(op, 1);
}

/**
 * @brief The ft_swap() function swaps the first two elements of the stack.
 * 
 * @param lst 
 * @param op
 */
void	ft_swap(t_list **list, char *op)
{
	int	tmp;

	tmp = (*list)->v;
	(*list)->v = (*list)->n->v;
	(*list)->n->v = tmp;
	ft_putstr_fd(op, 1);
}

/**
 * @brief The ft_reverse_rotate() function rotates the stack in the opposite
 * direction, moving all elements down by one, and the last element becomes the
 * first.
 * 
 * @param lst 
 * @param op
 */
void	ft_reverse_rotate(t_list **list, char *op)
{
	t_list	*last;
	t_list	*second_last;

	second_last = *list;
	last = ft_lstlast(*list);
	ft_lstadd_front(list, ft_lstnew(last->v));
	while (second_last->n->n)
		second_last = second_last->n;
	free(second_last->n);
	second_last->n = NULL;
	ft_putstr_fd(op, 1);
}
