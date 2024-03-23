/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juliencros <juliencros@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 10:52:56 by herbie            #+#    #+#             */
/*   Updated: 2024/03/22 10:28:09 by herbie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"
#include "window.h"
#include "ray.h"
#include "pixels.h"
#include "mlx/mlx.h"
#include <math.h>
#include <stdio.h>
#include <unistd.h>

// void ft_draw_line(t_data *data, int x1, int y1, int x2, int y2, int color)
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
// 		mlx_pixel_put(data->mlx_ptr, data->win_ptr, pixelX, pixelY, color);
// 		pixelX += deltaX;
// 		pixelY += deltaY;
// 		--pixels;
// 	}
// }

void ft_draw_vertical_line(t_data *data, int x, int y1, int y2, int color)
{
	while (y1 < y2)
	{
		mlx_pixel_put(data->mlx_ptr, data->win_ptr, x, y1, color);
		y1++;
	}
}

void ft_render(t_data *data)
{
	t_player *player = &data->player;

	for (int x = 0; x < WIN_WIDTH; x++)
	{

		// calculate ray position and direction
		double cameraX = 2 * x / (double)WIN_WIDTH - 1; // x-coordinate in camera spac
		double rayDirX = player->dx + player->px * cameraX;
		double rayDirY = player->dy + player->py * cameraX;

		int mapX = (int)player->x;
		int mapY = (int)player->y;

		// length of ray from current position to next x or y-side
		double sideDistX;
		double sideDistY;

		// length of ray from one x or y-side to next x or y-side
		double deltaDistX = (rayDirX == 0) ? 1e30 : fabs(1 / rayDirX);
		double deltaDistY = (rayDirY == 0) ? 1e30 : fabs(1 / rayDirY);
		double perpWallDist;
		// what direction to step in x or y-direction (either +1 or -1)
		int stepX;
		int stepY;

		int hit = 0; // was there a wall hit?
		int side;		 // was a NS or a EW wall hit?

		// calculate step and initial sideDist
		if (rayDirX < 0)
		{
			stepX = -1;
			sideDistX = (player->x - mapX) * deltaDistX;
		}
		else
		{
			stepX = 1;
			sideDistX = (mapX + 1.0 - player->x) * deltaDistX;
		}
		if (rayDirY < 0)
		{
			stepY = -1;
			sideDistY = (player->y - mapY) * deltaDistY;
		}
		else
		{
			stepY = 1;
			sideDistY = (mapY + 1.0 - player->y) * deltaDistY;
		}

		while (hit == 0)
		{
			// jump to next map square, either in x-direction, or in y-direction
			if (sideDistX < sideDistY)
			{
				sideDistX += deltaDistX;
				mapX += stepX;
				side = 0;
			}
			else
			{
				sideDistY += deltaDistY;
				mapY += stepY;
				side = 1;
			}

			// Check if ray has hit a wall
			if (data->map.map[mapX][mapY] > 0)
				hit = 1;
		}

		if (side == 0)
			perpWallDist = (sideDistX - deltaDistX);
		else
			perpWallDist = (sideDistY - deltaDistY);

		// Calculate height of line to draw on screen
		int lineHeight = (int)(WIN_HEIGHT / perpWallDist);

		// calculate lowest and highest pixel to fill in current stripe
		int drawStart = -lineHeight / 2 + WIN_HEIGHT / 2;
		if (drawStart < 0)
			drawStart = 0;
		int drawEnd = lineHeight / 2 + WIN_HEIGHT / 2;
		if (drawEnd >= WIN_HEIGHT)
			drawEnd = WIN_HEIGHT - 1;

		int color;

		switch (data->map.map[mapX][mapY])
		{
		case 1:
			color = 0xFF0000;
			break; // red
		case 2:
			color = 0x00FF00;
			break; // green
		case 3:
			color = 0x0000FF;
			break; // blue
		case 4:
			color = 0xFFFFFF;
			break; // white
		case 5:
			color = 0xFFFF00;
			break; // yellow
		case 6:
			color = 0x00FFFF;
			break; // cyan
		default:
			color = 0xFF00FF;
			break; // yellow
		}

		// (void)color;

		// give x and y sides different brightness
		// if (side == 1)
		// {
		// 	color = color / 2;
		// }

		// draw the pixels of the stripe as a vertical line

		// verLine(x, drawStart, drawEnd, color);
		// printf("drawStart: %d, drawEnd: %d\n", drawStart, drawEnd);
		// ft_draw_line(data, x, drawStart, x, drawEnd, color);
		ft_draw_vertical_line(data, x, drawStart, drawEnd, color);
	}
	// ft_cast_ray(data);
}
