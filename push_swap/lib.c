/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 19:59:31 by herbie            #+#    #+#             */
/*   Updated: 2023/02/18 19:01:19 by herbie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib.h"
#include "lists.h"

// void ft_replace_args_by_indices(int *args, int size)
// {
// 	int i;
// 	int j;
// 	int temp;

// 	i = 0;
// 	while (i < size)
// 	{
// 		j = 0;
// 		while (j < size)
// 		{
// 			if (args[i] < args[j])
// 			{
// 				temp = args[i];
// 				args[i] = args[j];
// 				args[j] = temp;
// 			}
// 			j++;
// 		}
// 		i++;
// 	}
// }

t_list *ft_fill_list_with_args(int *args, int size)
{
	t_list *list;
	int i;

	i = 1;
	list = ft_lstnew(args[0]);
	while (i < size)
	{
		ft_lstadd_back(&list, ft_lstnew(args[i]));
		i++;
	}
	return (list);
}

void ft_sort_large_array(int *args, int size)
{
	t_list *a;
	// t_list *b;

	a = ft_fill_list_with_args(args, size);
	// b = NULL;

	ft_lstprint(a);
}
