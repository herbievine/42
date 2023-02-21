/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 21:17:45 by herbie            #+#    #+#             */
/*   Updated: 2023/02/21 11:50:30 by herbie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "lists.h"

t_list	*ft_fill_list_with_args(int *args, int size);
int		ft_highest_value(t_list *list);
int		ft_is_sorted(t_list *list);
int		ft_replace_args_by_indices(int **args, int size);
int		ft_get_index_of(t_list *lst, int value);

#endif /* UTILS_H */