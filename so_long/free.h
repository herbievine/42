/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 12:40:41 by herbie            #+#    #+#             */
/*   Updated: 2023/04/20 15:06:25 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FREE_H
# define FREE_H

# include "structs.h"

void	ft_free_array(char **array, int n);
void	ft_free_2d_array(char ***array, int n);
void	ft_free_textures(t_data *data);
void	ft_free_mlx(t_data *data);
void	ft_free_data(t_data *data);

#endif /* FREE_H */
