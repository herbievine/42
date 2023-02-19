/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ops.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvine <hvine@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 14:58:05 by herbie            #+#    #+#             */
/*   Updated: 2023/02/19 13:12:19 by hvine            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ops.h"

/**
 * @brief The ft_r() function rotates the stack, moving all elements up by one,
 * and the last element becomes the first.
 *
 * @param lst
 */
void	ft_rotate(t_list **list)
{
	t_list *new_head;
	t_list *rotate;

	rotate = *list;
	new_head = (*list)->next;

	ft_lstadd_back(&new_head, rotate);
}