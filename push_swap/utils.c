/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 21:16:50 by herbie            #+#    #+#             */
/*   Updated: 2023/02/20 21:06:58 by herbie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "arrays.h"
#include "lists.h"
#include <stdlib.h>

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
		if (list->n != NULL && list->c > list->n->c)
			return (0);
		list = list->n;
	}
	return (1);
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
