/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lists.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/03 11:17:13 by herbie            #+#    #+#             */
/*   Updated: 2023/12/03 11:17:13 by herbie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LISTS_H
# define LISTS_H

void	ft_dcll_append(t_double_circular_ll **start,
			t_double_circular_ll *new_node);
void	ft_dcll_prepend(t_double_circular_ll **start,
			t_double_circular_ll *new_node);

#endif /* LISTS_H */