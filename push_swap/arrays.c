/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arrays.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 20:32:25 by herbie            #+#    #+#             */
/*   Updated: 2023/02/20 20:36:31 by herbie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arrays.h"

/**
 * @brief Sorts an array of integers in ascending order
 * 
 * @param arr 
 * @param size 
 */
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
