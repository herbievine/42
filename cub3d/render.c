/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 10:52:56 by herbie            #+#    #+#             */
/*   Updated: 2024/03/13 13:55:40 by herbie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"
#include "window.h"
#include "ray.h"
#include "mlx/mlx.h"
#include <math.h>
#include <time.h>
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

	printf("Player data: x: %f, y: %f, dx: %f, dy: %f, px: %f, py: %f\n", player->x, player->y, player->dx, player->dy, player->px, player->py);
	printf("move speed: %f, rot speed: %f\n", data->player.movespeed, data->player.rotspeed);

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
			if (data->map2[mapX][mapY] > 0)
			{
				hit = 1;
				printf("Hit a wall at x: %d, y: %d\n", mapX, mapY);
			}
		}

		if (side == 0)
			perpWallDist = (sideDistX - deltaDistX);
		else
			perpWallDist = (sideDistY - deltaDistY);

		// Calculate height of line to draw on screen
		int lineHeight = (int)(WIN_HEIGHT / perpWallDist);

		printf("lineHeight: %d\n", lineHeight);

		// calculate lowest and highest pixel to fill in current stripe
		int drawStart = -lineHeight / 2 + WIN_HEIGHT / 2;
		if (drawStart < 0)
			drawStart = 0;
		int drawEnd = lineHeight / 2 + WIN_HEIGHT / 2;
		if (drawEnd >= WIN_HEIGHT)
			drawEnd = WIN_HEIGHT - 1;

		int color;

		switch (data->map2[mapX][mapY])
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
		default:
			color = 0;
			break; // yellow
		}

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

	data->previous_frame_time = data->current_frame_time;
	data->current_frame_time = clock();
	double frameTime = (data->current_frame_time - data->previous_frame_time) / (double)1000; // the time in seconds it took to render the frame
	// printf("FPS: %f\n", 1.0 / frameTime);					// FPS counter

	// speed modifiers
	data->player.movespeed = frameTime * .2; // the constant value is in squares/second
	data->player.rotspeed = frameTime * .2;	 // the constant value is in radians/second
}
