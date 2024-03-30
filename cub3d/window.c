/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juliencros <juliencros@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 13:36:01 by herbie            #+#    #+#             */
/*   Updated: 2024/03/23 17:02:04 by juliencros       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"
#include "error.h"
#include "window.h"
#include "minimap.h"
#include "player.h"
#include "hooks.h"
#include "render.h"
#include "pixels.h"
#include "ray.h"
#include "ints.h"
// #include "hooks.h"
// #include "ints.h"
// #include "free.h"
// #include "textures.h"
// #include "str.h"
#include "mlx/mlx.h"
#include <stdlib.h>
#include <stdio.h>
#include <X11/X.h>
#include <X11/keysym.h>
#include <time.h>

int ft_on_render(t_data *data);

/**
 * @brief The ft_render_assets function renders the assets of the game. It
 * renders the player, the collectibles, and the exit.
 * 
 * @param data 
 */
// void	ft_render_assets(t_data *data)
// {
// 	int	i;
// 	int	j;

// 	i = -1;
// 	while (++i < data->map->height)
// 	{
// 		j = -1;
// 		while (++j < data->map->width)
// 		{
// 			if (i == data->map->start.y && j == data->map->start.x)
// 				mlx_put_image_to_window(
// 					data->mlx_ptr, data->win_ptr, data->textures[2],
// 					j * TILE_SIZE, i * TILE_SIZE + SCORE_OFFSET);
// 			else if (data->map->map[i][j] == COLL)
// 				mlx_put_image_to_window(
// 					data->mlx_ptr, data->win_ptr, data->textures[3],
// 					j * TILE_SIZE, i * TILE_SIZE + SCORE_OFFSET);
// 			else if (data->map->map[i][j] == EXIT && !data->map->collectibles)
// 				mlx_put_image_to_window(
// 					data->mlx_ptr, data->win_ptr, data->textures[4],
// 					j * TILE_SIZE, i * TILE_SIZE + SCORE_OFFSET);
// 		}
// 	}
// }

double	ft_calculate_fps(t_data *data)
{
	double	frame_time;

	data->previous_frame_time = data->current_frame_time;
	data->current_frame_time = clock();
	frame_time = (data->current_frame_time - data->previous_frame_time)
		/ (double)1000;
	data->player.movespeed = frame_time * 5;
	data->player.rotspeed = frame_time * 2;
	return (1.0 / frame_time);
}

void	ft_render_fps(t_data *data, double fps)
{
	char	*fps_str;
	int		i;
	int		j;

	fps_str = ft_itoa(fps);
	if (!fps_str)
		return ;
	i = 5;
	while (++i < 50)
	{
		j = -1;
		while (++j < 16)
			mlx_pixel_put(data->mlx_ptr, data->win_ptr, i, j, 0xFF0000);
	}
	mlx_string_put(
		data->mlx_ptr, data->win_ptr, 10, 12, 0xFFFFFF, "FPS: ");
	mlx_string_put(
		data->mlx_ptr, data->win_ptr, 35, 12, 0xFFFFFF, fps_str);
	free(fps_str);
}

void	ft_render_bg(t_data *data)
{
	int	x;
	int	y;

	x = 0;
	while (x < WIN_WIDTH)
	{
		y = 0;
		while (y < WIN_HEIGHT)
		{
			mlx_pixel_put(data->mlx_ptr, data->win_ptr, x, y, 0x000000);
			y++;
		}
		x++;
	}
}

/**
 * @brief The ft_on_render function is the main loop of the game. It gets
 * called every time the window needs to be refreshed. It renders the
 * background and the assets of the game.
 * 
 * @param data 
 * @return int 
 */
int	ft_on_render(t_data *data)
{
	t_ray		ray;
	double	fps;

	if (data->win_ptr == NULL)
		return (0);
	fps = ft_calculate_fps(data);
	ft_render_fps(data, fps);
	if (!data->player.is_moving)
		return (0);
	ft_create_pixel_map(data);
	ft_cast_ray(data, &ray);
	ft_draw_pixel_map(data, ray);
	// ft_render_bg(data);
	// ft_render_minimap(data);
	// ft_render_player(data);
	return (0);
}

/**
 * @brief The ft_init_window function initializes the window of the game. It
 * creates the window, loads the textures, and sets the hooks.
 * 
 * @param data 
 */
void	ft_init_window(t_data *data)
{
	data->win_ptr = mlx_new_window(
			data->mlx_ptr, WIN_WIDTH, WIN_HEIGHT, "franprix");
	if (!data->win_ptr)
		return (ft_err(EX11));
	mlx_hook(
		data->win_ptr, DestroyNotify, StructureNotifyMask, ft_on_close, data);
	mlx_hook(data->win_ptr, KeyPress, KeyPressMask, ft_on_keypress, data);
	mlx_hook(data->win_ptr, KeyRelease, KeyReleaseMask, ft_on_keyrelease, data);
	mlx_loop_hook(data->mlx_ptr, ft_on_render, data);
	mlx_loop(data->mlx_ptr);
}

// int ft_on_render(t_data *data)
// {
// 	double	fps;

// 	if (data->win_ptr == NULL)
// 		return (0);
// 	fps = ft_calculate_fps(data);
// 	ft_render_fps(data, fps);
// 	if (!data->player.is_moving)
// 		return (0);
// 	// ft_create_pixel_map(data);
// 	ft_render_bg(data);
// 	ft_render(data);
// 	printf("new player x: %f\n", data->player.x);
// 	printf("new player y: %f\n", data->player.y);
// 	printf("new player dx: %f\n", data->player.dx);
// 	printf("new player dy: %f\n", data->player.dy);
// 	printf("new player px: %f\n", data->player.px);
// 	printf("new player py: %f\n", data->player.py);
// 	// ft_cast_ray(data);
// 	// ft_render_bg(data);
// 	// ft_render_minimap(data);
// 	// ft_render_player(data);
// 	return (0);
// }