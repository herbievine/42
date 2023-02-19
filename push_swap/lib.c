/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 19:59:31 by herbie            #+#    #+#             */
/*   Updated: 2023/02/19 21:32:39 by herbie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib.h"
#include "lists.h"
#include "ops.h"
#include "math.h"
#include "display.h"
#include "sort.h"
#include <math.h>
#include <stdio.h>

t_list	*ft_fill_list_with_args(int *args, int size)
{
	t_list	*list;
	int		i;

	i = 1;
	list = ft_lstnew(args[0]);
	while (i < size)
	{
		ft_lstadd_back(&list, ft_lstnew(args[i]));
		i++;
	}
	return (list);
}

int	ft_is_sorted(t_list *list)
{
	while (list != NULL)
	{
		if (list->next != NULL && list->content > list->next->content)
			return (0);
		list = list->next;
	}
	return (1);
}

int	ft_is_stack_ready(t_list *list, int unit)
{
	while (list != NULL)
	{
		if (!(list->content >> unit & 1))
			return (0);
		list = list->next;
	}
	return (1);
}

// void	ft_print_stacks(t_list *a, t_list *b, char *op)
// {
// 	printf("--------%s--------\n", op);
// 	printf("| A:  ");
// 	while (a != NULL)
// 	{
// 		printf("%d ", a->content);
// 		a = a->next;
// 	}
// 	printf("\n");
// 	printf("| B:  ");
// 	while (b != NULL)
// 	{
// 		printf("%d ", b->content);
// 		b = b->next;
// 	}
// 	printf("\n");
// 	printf("------------------\n");
// }

void	ft_sort_large_array(int *args, int size)
{
	int		i;
	int		max_binary_length;
	t_list	*a;
	t_list	*b;

	a = ft_fill_list_with_args(args, size);
	b = NULL;
	i = -1;
	while (++i < size)
		if (ft_binary_length(args[i]) > max_binary_length)
			max_binary_length = ft_binary_length(args[i]);
	i = 0;
	while (i < max_binary_length && !ft_is_sorted(a))
	{
		while (!ft_is_stack_ready(a, i))
		{
			if ((a->content >> i) & 1)
			{
				ft_rotate(&a);
				ft_putstr_fd("ra\n", 1);
			}
			else
			{
				ft_push(&a, &b);
				ft_putstr_fd("pb\n", 1);
			}
		}
		while (b != NULL)
		{
			ft_push(&b, &a);
			ft_putstr_fd("pa\n", 1);
		}
		i++;
	}
	ft_lstclear(&a);
	ft_lstclear(&b);
}
