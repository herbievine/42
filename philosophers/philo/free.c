/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 12:41:40 by herbie            #+#    #+#             */
/*   Updated: 2023/04/27 16:59:10 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "free.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

/**
 * @brief The ft_free_array function takes in an array and frees all memory.
 * If n if provided, it will only free the memory of the first n elements.
 *
 * @param array
 * @param n
 */
void	ft_free_array(char **array, int n)
{
	int	i;

	i = -1;
	if (n == -1)
		while (array[++i])
			free(array[i]);
	else
		while (++i < n)
			if (array[i])
				free(array[i]);
	free(array);
}

/**
 * @brief The ft_free_2d_array function takes in a 2d array and frees all
 * memory. If n if provided, it will only free the memory of the first n
 * elements.
 *
 * @param array
 */
void	ft_free_2d_array(char ***array, int n)
{
	int	i;

	i = -1;
	if (n == -1)
		while (array[++i])
			ft_free_array(array[i], -1);
	else
		while (++i < n)
			if (array[i])
				ft_free_array(array[i], -1);
	free(array);
}
