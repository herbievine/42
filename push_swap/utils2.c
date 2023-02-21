/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 08:45:23 by herbie            #+#    #+#             */
/*   Updated: 2023/02/21 08:46:58 by herbie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "lists.h"
#include <stdlib.h>

int	ft_get_index_of(t_list *lst, int value)
{
	int	i;

	i = 0;
	while (lst != NULL)
	{
		if (lst->v == value)
			return (i);
		lst = lst->n;
		i++;
	}
	return (-1);	
}