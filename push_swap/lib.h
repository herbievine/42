/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/17 20:13:45 by herbie            #+#    #+#             */
/*   Updated: 2023/02/20 21:24:14 by herbie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIB_H
# define LIB_H

# include "lists.h"

void	ft_sort_args(int *args, int size);
void	ft_sort_three_array(t_list **a);
void	ft_sort_five_array(t_list **a, t_list **b);
void	ft_sort_large_array(t_list **a, t_list **b, int size);

#endif /* LIB_H */