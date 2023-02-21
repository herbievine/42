/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 19:59:31 by herbie            #+#    #+#             */
/*   Updated: 2023/02/21 11:32:00 by herbie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib.h"
#include "lists.h"
#include "utils.h"
#include "ops.h"
#include "display.h"
#include <stdio.h>

void	ft_sort_args(int *args, int size)
{
	t_list	*a;
	t_list	*b;

	a = ft_fill_list_with_args(args, size);
	b = NULL;
	if (ft_is_sorted(a))
		return ;
	else if (size == 2 && args[0] > args[1])
		ft_putstr_fd("sa\n", 1);
	else if (size == 3)
		ft_sort_three_array(&a);
	else if (size == 5)
		ft_sort_five_array(&a, &b);
	else
		ft_sort_large_array(&a, &b, size);
	ft_lstclear(&a);
	ft_lstclear(&b);
}

void	ft_sort_three_array(t_list **a)
{
	if ((*a)->v < (*a)->n->v && (*a)->v > (*a)->n->n->v)
		return (ft_reverse_rotate(a, "rra\n"));
	else if ((*a)->v > (*a)->n->n->v && (*a)->n->v < (*a)->n->n->v)
		return (ft_rotate(a, "ra\n"));
	else if ((*a)->v > (*a)->n->v && (*a)->n->v > (*a)->n->n->v)
		return (ft_swap(a, "sa\n"), ft_reverse_rotate(a, "rra\n"));
	else if ((*a)->v < (*a)->n->v && (*a)->n->v > (*a)->n->n->v)
		return (ft_swap(a, "sa\n"), ft_rotate(a, "ra\n"));
	else if ((*a)->v > (*a)->n->v && (*a)->n->v < (*a)->n->n->v)
		return (ft_swap(a, "sa\n"));
}

void	ft_sort_five_array(t_list **a, t_list **b)
{
	ft_push(a, b, "pb\n");
	ft_push(a, b, "pb\n");
	ft_sort_three_array(a);
	while ((*b) != NULL)
	{
		if (
			((*b)->v + 1 == (*a)->v)
			|| ((*b)->v == 0 && ft_lstlast(*a)->v == ft_highest_value(*a))
			|| ((*b)->v == 4 && ft_lstlast(*a)->v == ft_highest_value(*a))
		)
			ft_push(b, a, "pa\n");
		else if (((*b)->v - 1 == (*a)->v))
		{
			ft_rotate(a, "ra\n");
			ft_push(b, a, "pa\n");
		}
		else
			ft_rotate(a, "ra\n");
	}
	while (ft_get_index_of(*a, 0) > 2 && !ft_is_sorted(*a))
		ft_reverse_rotate(a, "rra\n");
	while (!ft_is_sorted(*a))
		ft_rotate(a, "ra\n");
}

void	ft_sort_large_array(t_list **a, t_list **b, int size)
{
	int	i;
	int	j;
	int	max_binary_length;

	i = -1;
	max_binary_length = 0;
	while (((size - 1) >> max_binary_length) != 0)
		max_binary_length++;
	i = -1;
	while (++i < max_binary_length && !ft_is_sorted(*a))
	{
		j = -1;
		while (++j < size)
		{
			if (((*a)->v >> i) & 1)
				ft_rotate(a, "ra\n");
			else
				ft_push(a, b, "pb\n");
		}
		while (*b != NULL)
			ft_push(b, a, "pa\n");
	}
}
