/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 19:59:31 by herbie            #+#    #+#             */
/*   Updated: 2023/02/18 21:03:59 by herbie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib.h"
#include "lists.h"

void ft_sort_int_tab(int **arr, int size)
{
	int i;
	int j;
	int temp;

	i = 0;
	while (i < size)
	{
		j = i + 1;
		while (j < size)
		{
			if ((*arr)[i] > (*arr)[j])
			{
				temp = (*arr)[i];
				(*arr)[i] = (*arr)[j];
				(*arr)[j] = temp;
			}
			j++;
		}
		i++;
	}
}

void ft_replace_args_by_indices(int **args, int size)
{
	int i;
	int j;
	int *sortedArray;

	i = -1;
	j = -1;
	sortedArray = (int *)malloc(size * sizeof(int));
	while (++i < size)
		sortedArray[i] = (*args)[i];
	ft_sort_int_tab(&sortedArray, size);
	i = -1;
	while (++i < size)
	{
		j = -1;
		while (++j < size)
		{
			if ((*args)[i] == sortedArray[j])
			{
				(*args)[i] = j;
				break;
			}
		}
	}
}

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

	ft_replace_args_by_indices(&args, size);
	a = ft_fill_list_with_args(args, size);
	// b = NULL;

	ft_lstprint(a);
}
