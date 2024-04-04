/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcros <jcros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 12:40:41 by herbie            #+#    #+#             */
/*   Updated: 2024/04/04 14:43:41 by jcros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FREE_H
# define FREE_H

# include "structs.h"

void	ft_free_array(char **array, int n);
void	ft_free_void_array(void **array, int n);
void	ft_free_2d_array(void ***array, int n);
void	ft_free_mlx(t_data *data);
void	ft_free_data(t_data *data);
void    ft_free_and_null(void ***ptr, int n);

#endif /* FREE_H */
