/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arrays.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 20:31:48 by herbie            #+#    #+#             */
/*   Updated: 2023/02/22 08:56:38 by herbie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ARRAYS_H
# define ARRAYS_H

# include "structs.h"

void	ft_sort_int_array(int **arr, int size);
t_list	*ft_fill_list_with_args(int *args, int size);

#endif /* ARRAYS_H */
