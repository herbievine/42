/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvine <hvine@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 19:59:31 by herbie            #+#    #+#             */
/*   Updated: 2023/02/19 14:45:34 by hvine            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib.h"
#include "lists.h"
#include "num.h"

void	ft_sort_int_tab(int **arr, int size)
{
	int	i;
	int	j;
	int	temp;

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

void	ft_replace_args_by_indices(int **args, int size)
{
	int	i;
	int	j;
	int	*sorted_array;

	i = -1;
	j = -1;
	sorted_array = (int *)malloc(size * sizeof(int));
	while (++i < size)
		sorted_array[i] = (*args)[i];
	ft_sort_int_tab(&sorted_array, size);
	i = -1;
	while (++i < size)
	{
		j = -1;
		while (++j < size)
		{
			if ((*args)[i] == sorted_array[j])
			{
				(*args)[i] = j;
				break ;
			}
		}
	}
	free(sorted_array);
}

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

void	ft_sort_large_array(int *args, int size)
{
	t_list	*a;
	t_list	*b;

	ft_replace_args_by_indices(&args, size);
	a = ft_fill_list_with_args(args, size);
	printf("sorted: %d\n", ft_is_sorted(a));
	ft_lstprint(a);
	ft_lstclear(&a);
}
