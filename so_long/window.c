/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 13:36:01 by herbie            #+#    #+#             */
/*   Updated: 2023/05/07 19:47:55 by herbie           ###   ########.fr       */
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

int	ft_render(t_data *data)
{
	if (data->win_ptr == NULL)
		return (0);
	ft_render_bg(data);
	ft_render_assets(data);
	return (0);
}

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
	mlx_loop_hook(data->mlx_ptr, &ft_render, data);
	mlx_hook(data->win_ptr, KeyRelease, KeyReleaseMask, &on_keypress, data);
	mlx_hook(
		data->win_ptr, DestroyNotify, StructureNotifyMask, &on_destroy, data);
	mlx_loop(data->mlx_ptr);
	return (ft_free_textures(data), ft_free_mlx(data), ft_free_data(data));
}
