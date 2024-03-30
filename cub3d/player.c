/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juliencros <juliencros@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 13:38:21 by herbie            #+#    #+#             */
/*   Updated: 2024/03/30 17:00:40 by juliencros       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "player.h"
#include "mlx/mlx.h"
#include <stdio.h>

// Long = E W
// Lat = N S

void	ft_init_player(t_player *player, t_data *data)
{
	player->y = data->map.start_row + 0.5;
	player->x = data->map.start_col + 0.5;
	if (data->map.start_dir == NORTH || data->map.start_dir == SOUTH)
		ft_init_lat(player, data);
	else
		ft_init_long(player, data);
}

void	ft_init_long(t_player *player, t_data *data)
{
	if (data->map.start_dir == EAST)
	{
		player->dx = 1;
		player->dy = 0;
		player->px = 0;
		player->py = 0.66;
	}
	else
	{
		player->dx = -1;
		player->dy = 0;
		player->px = 0;
		player->py = -0.66;
	}
}

void	ft_init_lat(t_player *player, t_data *data)
{
	if (data->map.start_dir == NORTH)
	{
		player->dx = 0;
		player->dy = -1;
		player->px = 0.66;
		player->py = 0;
	}
	else
	{
		player->dx = 0;
		player->dy = 1;
		player->px = -0.66;
		player->py = 0;
	}
}