/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 13:36:01 by herbie            #+#    #+#             */
/*   Updated: 2024/03/20 16:46:07 by herbie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"
#include "error.h"
#include "window.h"
#include "minimap.h"
#include "player.h"
#include "hooks.h"
#include "render.h"
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
	data->player.rotspeed = frame_time * 3;
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
			mlx_pixel_put(data->mlx_ptr, data->win_ptr, i, j, 0x0000FF00);
	}
	mlx_string_put(
		data->mlx_ptr, data->win_ptr, 10, 12, 0x00FF0000, "FPS: ");
	mlx_string_put(
		data->mlx_ptr, data->win_ptr, 35, 12, 0x00FF0000, fps_str);
	free(fps_str);
}

// /**
//  * @brief The ft_render_bg function renders the background of the game. It
//  * handles the rendering of the floor and the walls.
//  * 
//  * @param data 
//  */
// void	ft_render_bg(t_data *data)
// {
// 	int	i;
// 	int	j;

// 	i = -1;
// 	while (++i < data->map->height)
// 	{
// 		j = -1;
// 		while (++j < data->map->width)
// 		{
// 			if (data->map->map[i][j] == WALL)
// 				mlx_put_image_to_window(
// 					data->mlx_ptr, data->win_ptr, data->textures[1],
// 					j * TILE_SIZE, i * TILE_SIZE + SCORE_OFFSET);
// 			else if (!(i == data->map->start.y && j == data->map->start.x)
// 				&& (data->map->map[i][j] != EXIT || data->map->collectibles)
// 				&& data->map->map[i][j] != COLL)
// 				mlx_put_image_to_window(
// 					data->mlx_ptr, data->win_ptr, data->textures[0],
// 					j * TILE_SIZE, i * TILE_SIZE + SCORE_OFFSET);
// 		}
// 	}
// }

// void	ft_display_score(t_data *data)
// {
// 	char	*moves;
// 	char	*tmp;
// 	int		i;
// 	int		j;

// 	moves = ft_itoa(data->map->moves);
// 	if (!moves)
// 		return ;
// 	tmp = ft_strjoin("moves: ", moves);
// 	free(moves);
// 	if (!tmp)
// 		return ;
// 	i = -1;
// 	while (++i < data->map->width * TILE_SIZE)
// 	{
// 		j = -1;
// 		while (++j < SCORE_OFFSET)
// 			mlx_pixel_put(data->mlx_ptr, data->win_ptr, i, j, 0x00000000);
// 	}
// 	mlx_string_put(
// 		data->mlx_ptr, data->win_ptr, 10, 30, 0x00FF0000, tmp);
// 	free(tmp);
// }

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
			mlx_pixel_put(data->mlx_ptr, data->win_ptr, x, y, 0x00000000);
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
	double	fps;
	if (data->win_ptr == NULL)
		return (0);
	fps = ft_calculate_fps(data);
	ft_render_fps(data, fps);
	if (!data->player.is_moving)
		return (0);
	printf("re-rendering...\n");
	ft_render_bg(data);
	ft_render(data);
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
	data->mlx_ptr = mlx_init();
	if (!data->mlx_ptr)
		return (ft_err(EX11));
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