/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcros <jcros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 13:38:21 by herbie            #+#    #+#             */
/*   Updated: 2024/04/02 16:04:29 by jcros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "player.h"
#include "mlx/mlx.h"
#include <stdio.h>

static void	ft_init_long(t_player *player, t_data *data);
static void	ft_init_lat(t_player *player, t_data *data);

/**
 * @brief initialize the player structure with the starting position
 * 	and direction.
 * @param player
 * @param data
 * @return void
 */
void	ft_init_player(t_player *player, t_data *data)
{
	player->y = data->map.start_row + 0.5;
	player->x = data->map.start_col + 0.5;
	player->is_moving = false;
	if (data->map.start_dir == NORTH || data->map.start_dir == SOUTH)
		ft_init_lat(player, data);
	else
		ft_init_long(player, data);
}

/**
 * @brief initialize the player position with the starting position and direction
 * 	when the direction is EAST or WEST.
 * @param player
 * @param data
 * @return void
 */
static void	ft_init_long(t_player *player, t_data *data)
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

/**
 * @brief initialize the player position with the starting position and direction
 * 	when the direction is NORTH or SOUTH.
 * @param player
 * @param data
 * @return void
 */
static void	ft_init_lat(t_player *player, t_data *data)
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
