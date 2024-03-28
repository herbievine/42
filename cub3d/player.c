/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juliencros <juliencros@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 13:38:21 by herbie            #+#    #+#             */
/*   Updated: 2024/03/28 15:37:46 by juliencros       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "player.h"
#include "mlx/mlx.h"
#include <stdio.h>

void	ft_init_player(t_player *player, t_data *data)
{
	player->y = data->map.start_row;
	player->x = data->map.start_col;
	if (data->map.start_dir ==  NORTH)
	{
		player->dx = 0;
		player->dy = -1;
		player->px = 0.66;
		player->py = 0;
	}
	else if (data->map.start_dir == SOUTH)
	{
		player->dx = 0;
		player->dy = 1;
		player->px = -0.66;
		player->py = 0;
	}
	else if (data->map.start_dir == EAST)
	{
		player->dx = 1;
		player->dy = 0;
		player->px = 0;
		player->py = 0.66;
	}
	else if (data->map.start_dir == WEST)
	{
		player->dx = -1;
		player->dy = 0;
		player->px = 0;
		player->py = -0.66;
	}
}
