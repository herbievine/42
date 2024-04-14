/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixels.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 16:25:30 by herbie            #+#    #+#             */
/*   Updated: 2024/03/22 09:31:56 by herbie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIXELS_H
# define PIXELS_H

# include "structs.h"
# include <stdbool.h>

bool	ft_create_texture_buffer_from_img(t_data *data,
			t_img *img, t_cardinal_direction dir);
bool	ft_create_pixel_map(t_data *data);
void	ft_update_pixel_map(t_data *data, t_ray *ray, int x);
void	ft_draw_pixel_map(t_data *data);

#endif /* PIXELS_H */
