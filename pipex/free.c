/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 12:41:40 by herbie            #+#    #+#             */
/*   Updated: 2023/04/05 10:33:15 by herbie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "free.h"
#include <stdlib.h>

void	ft_free_array(char **array, int size)
{
	int	i;

	i = -1;
	if (size == -1)
		while (array[++i])
			free(array[i]);
	else
		while (++i < size)
			if (array[i])
				free(array[i]);
	free(array);
}

void	ft_free_2d_array(char ***array)
{
	int	i;

	i = -1;
	while (array[++i])
		ft_free_array(array[i], -1);
	free(array);
}
