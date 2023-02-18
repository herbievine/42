/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ops.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 14:58:05 by herbie            #+#    #+#             */
/*   Updated: 2023/02/18 16:04:21 by herbie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ops.h"

/**
 * @brief The ft_ra() function rotates the a stack, moving all elements up by one,
 * and the last element becomes the first.
 *
 * @param a Stack A
 * @param b Stack B
 */
void ft_ra(t_list **a)
{
	t_list *new_head;
	t_list *rotate;

	rotate = *a;
	new_head = (*a)->next;

	ft_lstadd_back(&new_head, rotate);
}