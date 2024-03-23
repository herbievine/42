/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juliencros <juliencros@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 13:38:21 by herbie            #+#    #+#             */
/*   Updated: 2024/03/23 17:28:31 by juliencros       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "player.h"
#include "mlx/mlx.h"
#include <stdio.h>

void	ft_init_player(t_player *player, t_data *data)
{
	player->x = data->map.start_row;
	player->y = data->map.start_col;
	if (data->map.start_dir ==  NORTH)
	{
		player->dx = -1;
		player->dy = 0;
		player->px = 0;
		player->py = -0.66;
	}
	else if (data->map.start_dir == SOUTH)
	{
		player->dx = 1;
		player->dy = 0;
		player->px = 0;
		player->py = 0.66;
	}
	else if (data->map.start_dir == EAST)
	{
		player->dx = 0;
		player->dy = 1;
		player->px = -0.66;
		player->py = 0;
	}
	else if (data->map.start_dir == WEST)
	{
		player->dx = 0;
		player->dy = -1;
		player->px = 0.66;
		player->py = 0;
	}
}

void	ft_render_player(t_data *data)
{
	int x = data->player.x;
	int y = data->player.y;

	mlx_pixel_put(data->mlx_ptr, data->win_ptr, x, y, 0x00FF00);
	mlx_pixel_put(data->mlx_ptr, data->win_ptr, x + 1, y, 0x00FF00);
	mlx_pixel_put(data->mlx_ptr, data->win_ptr, x, y + 1, 0x00FF00);
	mlx_pixel_put(data->mlx_ptr, data->win_ptr, x + 1, y + 1, 0x00FF00);
}

void	ft_move_player(t_data *data, int key)
{
	if (key == KEY_W)
		data->player.y -= 10;
	else if (key == KEY_A)
		data->player.x -= 10;
	else if (key == KEY_S)
		data->player.y += 10;
	else if (key == KEY_D)
		data->player.x += 10;
}