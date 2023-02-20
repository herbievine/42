/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 21:17:45 by herbie            #+#    #+#             */
/*   Updated: 2023/02/20 20:36:29 by herbie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "lists.h"

t_list	*ft_fill_list_with_args(int *args, int size);
int		ft_is_sorted(t_list *list);
void	ft_replace_args_by_indices(int **args, int size);

#endif /* UTILS_H */