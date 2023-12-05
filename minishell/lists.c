/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lists.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/03 10:52:22 by herbie            #+#    #+#             */
/*   Updated: 2023/12/03 11:22:08 by herbie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"
#include "lists.h"
#include <stdlib.h>

/**
 * @brief The ft_dcll_append function appends a new node to the end of the list
 * 
 * @param start 
 * @param new_node 
 */
void	ft_dcll_append(t_double_circular_ll **start,
	t_double_circular_ll *new_node)
{
	t_double_circular_ll	*last;

	if (*start == NULL)
		return (*start = new_node, (void)0);
	last = (*start)->prev;
	new_node->next = *start;
	(*start)->prev = new_node;
	new_node->prev = last;
	last->next = new_node;
}

/**
 * @brief The ft_dcll_prepend function prepends a new node to the start of the
 * list
 * 
 * @param start 
 * @param new_node 
 */
void	ft_dcll_prepend(t_double_circular_ll **start,
	t_double_circular_ll *new_node)
{
	t_double_circular_ll	*last;

	last = (*start)->prev;
	new_node->next = *start;
	new_node->prev = last;
	last->next = new_node;
	(*start)->prev = new_node;
	*start = new_node;
}
