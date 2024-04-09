/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcros <jcros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 13:36:01 by herbie            #+#    #+#             */
/*   Updated: 2024/04/08 19:19:44 by jcros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"
#include "error.h"
#include "window.h"
#include "free.h"
#include "player.h"
#include "hooks.h"
#include "pixels.h"
#include "ray.h"
#include "ints.h"
#include "move.h"
#include "mlx/mlx.h"
#include <stdlib.h>
#include <stdio.h>
#include <X11/X.h>
#include <X11/keysym.h>
#include <time.h>

double	ft_calculate_fps(t_data *data)
{
	double	frame_time;

	data->previous_frame_time = data->current_frame_time;
	data->current_frame_time = clock();
	frame_time = (data->current_frame_time - data->previous_frame_time) * 1000.0 / CLOCKS_PER_SEC;
	data->player.movespeed = frame_time * 5;
	data->player.rotspeed = frame_time * 2;
	return (frame_time);
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

void	ft_render(t_data *data)
{
	t_ray	ray;

	if (!ft_create_pixel_map(data))
		return ;
	ft_cast_ray(data, &ray);
	ft_draw_pixel_map(data);
	ft_free_void_array((void **)data->pixels, WIN_HEIGHT);
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
	ft_move_player(data);
	if (data->player.is_moving)
		ft_render(data);
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
		return (ft_free_mlx(data), ft_err(EX11));
	ft_render(data);
	mlx_hook(
		data->win_ptr, DestroyNotify, StructureNotifyMask, ft_on_close, data);
	mlx_hook(data->win_ptr, KeyPress, KeyPressMask, ft_on_keypress, data);
	mlx_hook(data->win_ptr, KeyRelease, KeyReleaseMask, ft_on_keyrelease, data);
	mlx_loop_hook(data->mlx_ptr, ft_on_render, data);
	mlx_loop(data->mlx_ptr);
}
