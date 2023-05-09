/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 13:36:01 by herbie            #+#    #+#             */
/*   Updated: 2023/05/08 13:21:47 by herbie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "window.h"
#include "structs.h"
#include "hooks.h"
#include "error.h"
#include "free.h"
#include "textures.h"
#include "mlx/mlx.h"
#include <stdlib.h>
#include <stdio.h>
#include <X11/X.h>
#include <X11/keysym.h>

/**
 * @brief The ft_render_assets function renders the assets of the game. It
 * renders the player, the collectibles, and the exit.
 * 
 * @param data 
 */
void	ft_render_assets(t_data *data)
{
	int	i;
	int	j;

	i = -1;
	while (++i < data->map->height)
	{
		j = -1;
		while (++j < data->map->width)
		{
			if (i == data->map->start.y && j == data->map->start.x)
				mlx_put_image_to_window(
					data->mlx_ptr, data->win_ptr, data->textures[2],
					j * TILE_SIZE, i * TILE_SIZE);
			else if (data->map->map[i][j] == COLL)
				mlx_put_image_to_window(
					data->mlx_ptr, data->win_ptr, data->textures[3],
					j * TILE_SIZE, i * TILE_SIZE);
			else if (data->map->map[i][j] == EXIT && !data->map->collectibles)
				mlx_put_image_to_window(
					data->mlx_ptr, data->win_ptr, data->textures[4],
					j * TILE_SIZE, i * TILE_SIZE);
		}
	}
}

/**
 * @brief The ft_render_bg function renders the background of the game. It
 * handles the rendering of the floor and the walls.
 * 
 * @param data 
 */
void	ft_render_bg(t_data *data)
{
	int	i;
	int	j;

	i = -1;
	while (++i < data->map->height)
	{
		j = -1;
		while (++j < data->map->width)
		{
			if (data->map->map[i][j] == WALL)
				mlx_put_image_to_window(
					data->mlx_ptr, data->win_ptr, data->textures[1],
					j * TILE_SIZE, i * TILE_SIZE);
			else if (!(i == data->map->start.y && j == data->map->start.x)
				&& (data->map->map[i][j] != EXIT || data->map->collectibles)
				&& data->map->map[i][j] != COLL)
				mlx_put_image_to_window(
					data->mlx_ptr, data->win_ptr, data->textures[0],
					j * TILE_SIZE, i * TILE_SIZE);
		}
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
	if (data->win_ptr == NULL)
		return (0);
	ft_render_bg(data);
	ft_render_assets(data);
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
		return (ft_free_data(data), ft_err(EX11));
	data->win_ptr = mlx_new_window(
			data->mlx_ptr, data->map->width * TILE_SIZE,
			data->map->height * TILE_SIZE, "herbie: so_long");
	if (!data->win_ptr)
		return (ft_free_mlx(data), ft_free_data(data), ft_err(EX11));
	if (!ft_load_textures(data))
		return (ft_free_mlx(data), ft_free_data(data), ft_err(ETXTUR));
	mlx_loop_hook(data->mlx_ptr, &ft_on_render, data);
	mlx_hook(data->win_ptr, KeyRelease, KeyReleaseMask, &ft_on_keypress, data);
	mlx_hook(
		data->win_ptr, DestroyNotify, StructureNotifyMask, &ft_on_close, data);
	mlx_loop(data->mlx_ptr);
	return (ft_free_textures(data), ft_free_mlx(data), ft_free_data(data));
}
