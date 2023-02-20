/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 19:59:31 by herbie            #+#    #+#             */
/*   Updated: 2023/02/20 23:07:38 by herbie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib.h"
#include "lists.h"
#include "utils.h"
#include "ops.h"
#include "display.h"
#include <stdio.h>

void ft_print_stacks(t_list *a, t_list *b, char *op)
{
	printf("--------%s--------\n", op);
	printf("| A:  ");
	while (a != NULL)
	{
		printf("%d ", a->val);
		a = a->n;
	}
	printf("\n");
	printf("| B:  ");
	while (b != NULL)
	{
		printf("%d ", b->val);
		b = b->n;
	}
	printf("\n");
	printf("------------------\n");
}

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
	if ((*a)->val < (*a)->n->val && (*a)->val > (*a)->n->n->val)
		return (ft_reverse_rotate(a, "rra\n"));
	else if ((*a)->val > (*a)->n->n->val && (*a)->n->val < (*a)->n->n->val)
		return (ft_rotate(a, "ra\n"));
	else if ((*a)->val > (*a)->n->val && (*a)->n->val > (*a)->n->n->val)
		return (ft_swap(a, "sa\n"), ft_reverse_rotate(a, "rra\n"));
	else if ((*a)->val < (*a)->n->val && (*a)->n->val > (*a)->n->n->val)
		return (ft_swap(a, "sa\n"), ft_rotate(a, "ra\n"));
	else if ((*a)->val > (*a)->n->val && (*a)->n->val < (*a)->n->n->val)
		return (ft_swap(a, "sa\n"));
}

void	ft_sort_five_array(t_list **a, t_list **b)
{
	int i;

	ft_push(a, b, "pb\n");
	ft_push(a, b, "pb\n");
	ft_sort_three_array(a);
	//ft_print_stacks(*a, *b, "start");
	i = -1;
	while (++i < 3 && (*b) != NULL)
	{
		// if (
		// 	((*b)->val - ft_highest_value(*a) > 1)
		// 	&& ((*a)->val == ft_highest_value(*a))
		// )
		// {
		// 	ft_putstr_fd("FUNC1", 1);
		// 	ft_rotate(a, "ra\n");
		// 	ft_push(b, a, "pa\n");
		// 	break ;
		// }
		if ((*b)->val - 1 == (*a)->val)
		{
			// ft_putstr_fd("FUNC1", 1);
			ft_rotate(a, "ra\n");
			ft_push(b, a, "pa\n");
			break ;
		}
		if (((*b)->val + 1 == (*a)->val)) // else if ((*b)->val + 1 == (*a)->val)
		{
			// ft_putstr_fd("FUNC2", 1);
			ft_push(b, a, "pa\n");
			break ;
		}
		else
		{
			// ft_putstr_fd("FUNC3", 1);
			ft_rotate(a, "ra\n");
		}
	}
	//ft_print_stacks(*a, *b, "mid start");
	i = -1;
	while (++i < 4 && (*b) != NULL)
	{
		if ((*b)->val - 1 == (*a)->val)
		{
			// ft_putstr_fd("FUNC1", 1);
			ft_rotate(a, "ra\n");
			ft_push(b, a, "pa\n");
			break ;
		}
		if (((*b)->val + 1 == (*a)->val))
		{
			ft_push(b, a, "pa\n");
			break ;
		}
		else
			ft_rotate(a, "ra\n");
	}
	//ft_print_stacks(*a, *b, "mid end");
	while (!ft_is_sorted(*a))
		ft_rotate(a, "ra\n");
	//ft_print_stacks(*a, *b, "end");
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
			if (((*a)->val >> i) & 1)
				ft_rotate(a, "ra\n");
			else
				ft_push(a, b, "pb\n");
		}
		while (*b != NULL)
			ft_push(b, a, "pa\n");
	}
}
