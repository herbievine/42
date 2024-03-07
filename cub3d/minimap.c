/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 09:30:53 by herbie            #+#    #+#             */
/*   Updated: 2024/03/04 09:30:53 by herbie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minimap.h"
#include "window.h"
#include "mlx/mlx.h"
#include <math.h>

#define OFFSET 10
#define SIZE 80

// void	ft_draw_line(t_data *data, int x1, int y1, int x2, int y2)
// {
// 	double deltaX = x2 - x1;
// 	double deltaY = y2 - y1;

// 	int pixels = sqrt((deltaX * deltaX) + (deltaY * deltaY));

// 	deltaX /= pixels;
// 	deltaY /= pixels;

// 	double pixelX = x1;
// 	double pixelY = y1;
// 	while (pixels)
// 	{
// 			mlx_pixel_put(data->mlx_ptr, data->win_ptr, pixelX, pixelY, 0xFFFFFF);
// 			pixelX += deltaX;
// 			pixelY += deltaY;
// 			--pixels;
// 	}
// }

void	ft_draw_outline(t_data *data)
{
	(void)data;
	// draw top line
	// ft_draw_line(data, OFFSET, OFFSET, OFFSET + SIZE, OFFSET);
	// // draw bottom line
	// ft_draw_line(data, OFFSET, OFFSET + SIZE, OFFSET + SIZE, OFFSET + SIZE);
	// // draw left line
	// ft_draw_line(data, OFFSET, OFFSET, OFFSET, OFFSET + SIZE);
	// // draw right line
	// ft_draw_line(data, OFFSET + SIZE, OFFSET, OFFSET + SIZE, OFFSET + SIZE);
}

void	ft_render_minimap(t_data *data)
{
	ft_draw_outline(data);
}