/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 13:36:01 by herbie            #+#    #+#             */
/*   Updated: 2023/05/07 18:33:04 by herbie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "window.h"
#include "structs.h"
#include "hooks.h"
#include "free.h"
#include "mlx/mlx.h"
#include <stdlib.h>
#include <stdio.h>
#include <X11/X.h>
#include <X11/keysym.h>

#define TILE_SIZE 48
#define EMPT_PATH "./assets/floor.xpm"
#define WALL_PATH "./assets/wall.xpm"

t_bool	ft_init_assets(t_data *data)
{
	int	size;

	size = TILE_SIZE;
	data->assets[0].mlx_img = mlx_xpm_file_to_image(
			data->mlx_ptr, EMPT_PATH, &size, &size);
	data->assets[0].id = EMPT;
	data->assets[1].mlx_img = mlx_xpm_file_to_image(
			data->mlx_ptr, WALL_PATH, &size, &size);
	data->assets[1].id = WALL;
	return (true);
}

// void	ft_render_bg(t_data *data)
// {
// 	int	i;
// 	int	j;

// 	if (data->win_ptr == NULL)
// 		return ;
// 	i = -1;
// 	while (++i < 300)
// 	{
// 		j = -1;
// 		while (++j < 600)
// 			mlx_pixel_put(data->mlx_ptr, data->win_ptr, j++, i, BG_COLOR);
// 	}
// }

void	ft_render_bg(t_data *data)
{
	int	i;
	int	j;

	if (data->win_ptr == NULL)
		return ;
	i = -1;
	while (++i < data->map->height)
	{
		j = -1;
		while (++j < data->map->width)
		{
			if (data->map->map[i][j] == WALL)
				mlx_put_image_to_window(
					data->mlx_ptr, data->win_ptr, data->assets[1].mlx_img,
					j * TILE_SIZE, i * TILE_SIZE);
			else
				mlx_put_image_to_window(
					data->mlx_ptr, data->win_ptr, data->assets[0].mlx_img,
					j * TILE_SIZE, i * TILE_SIZE);
		}
	}
}

int	ft_render(t_data *data)
{
	if (data->win_ptr == NULL)
		return (0);
	ft_render_bg(data);
	return (0);
}

void	ft_init_window(t_data *data)
{
	data->mlx_ptr = mlx_init();
	if (data->mlx_ptr == NULL)
		return (ft_free_data(data));
	data->win_ptr = mlx_new_window(
			data->mlx_ptr, data->map->width * TILE_SIZE,
			data->map->height * TILE_SIZE, "herbie: so_long");
	if (data->win_ptr == NULL)
		return (ft_free_data(data));
	if (!ft_init_assets(data))
		return (ft_free_data(data));
	mlx_loop_hook(data->mlx_ptr, &ft_render, data);
	mlx_hook(data->win_ptr, KeyRelease, KeyReleaseMask, &on_keypress, data);
	mlx_hook(
		data->win_ptr, DestroyNotify, StructureNotifyMask, &on_destroy, data);
	mlx_loop(data->mlx_ptr);
	mlx_destroy_display(data->mlx_ptr);
	ft_free_data(data);
}
