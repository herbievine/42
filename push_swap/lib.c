/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 19:59:31 by herbie            #+#    #+#             */
/*   Updated: 2023/02/20 18:21:55 by herbie           ###   ########.fr       */
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

void	ft_sort_args(int *args, int size)
{
	t_list	*a;
	t_list	*b;

	a = ft_fill_list_with_args(args, size);
	b = NULL;
	if (size <= 5)
		printf("Not implemented yet");
	else
		ft_sort_large_array(&a, &b, size);
	ft_lstclear(&a);
	ft_lstclear(&b);
}

// void ft_print_stacks(t_list *a, t_list *b, char *op)
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

void	ft_sort_large_array(t_list **a, t_list **b, int size)
{
	int	i;
	int	j;
	int	max_binary_length;

	i = -1;
	while ((size - 1 >> max_binary_length) != 0)
		max_binary_length++;
	i = -1;
	while (++i < max_binary_length && !ft_is_sorted(*a))
	{
		j = -1;
		while (++j < size)
		{
			if (((*a)->content >> i) & 1)
				ft_rotate(a, "ra\n");
			else
				ft_push(a, b, "pb\n");
		}
		while (*b != NULL)
			ft_push(b, a, "pa\n");
	}
}
