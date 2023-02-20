/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ops.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 14:58:05 by herbie            #+#    #+#             */
/*   Updated: 2023/02/20 21:06:58 by herbie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "display.h"
#include "ops.h"

/**
 * @brief The ft_rotate() function rotates the stack, moving all elements up by
 * one, and the last element becomes the first.
 *
 * @param lst
 * @param op
 */
void	ft_rotate(t_list **list, char *op)
{
	t_list	*last;
	t_list	*tmp;

	last = ft_lstlast(*list);
	tmp = ft_lstnew((*list)->c);
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

	tmp = ft_lstnew((*src)->c);
	if (!*dst)
		*dst = ft_lstnew((*src)->c);
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

	tmp = (*list)->c;
	(*list)->c = (*list)->n->c;
	(*list)->n->c = tmp;
	ft_putstr_fd(op, 1);
}

/**
 * @brief The ft_reverse_rotate() function rotates the stack in the opposite
 * direction, moving all elements down by one, and the first element becomes the
 * last.
 * 
 * @param lst 
 * @param op
 */
void	ft_reverse_rotate(t_list **list, char *op)
{
	t_list	*last;
	t_list	*tmp;

	last = ft_lstlast(*list);
	tmp = ft_lstnew(last->c);
	ft_lstadd_front(list, tmp);
	while ((*list)->n->n)
		*list = (*list)->n;
	free((*list)->n);
	(*list)->n = NULL;
	ft_putstr_fd(op, 1);
}
