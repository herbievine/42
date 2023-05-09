/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 14:33:04 by herbie            #+#    #+#             */
/*   Updated: 2023/05/08 13:21:47 by herbie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hooks.h"
#include "structs.h"
#include "free.h"
#include "mlx/mlx.h"
#include "print.h"
#include <stdlib.h>
#include <stdio.h>
#include <X11/keysym.h>

/**
 * @brief The ft_handle_move function handles the movement of the player. It
 * checks if the player is moving into a wall, and if not, it moves the player
 * and increments the move counter.
 * 
 * @param keysym 
 * @param data 
 */
void	ft_handle_move(int keysym, t_data *data)
{
	if (keysym == XK_Up
		&& data->map->map[data->map->start.y - 1][data->map->start.x] != WALL
		&& ++data->map->moves
		&& ft_dprintf(1, "You have moved %d time(s).\n", data->map->moves))
		--data->map->start.y;
	else if (keysym == XK_Down
		&& data->map->map[data->map->start.y + 1][data->map->start.x] != WALL
		&& ++data->map->moves
		&& ft_dprintf(1, "You have moved %d time(s).\n", data->map->moves))
		++data->map->start.y;
	else if (keysym == XK_Left
		&& data->map->map[data->map->start.y][data->map->start.x - 1] != WALL
		&& ++data->map->moves
		&& ft_dprintf(1, "You have moved %d time(s).\n", data->map->moves))
		--data->map->start.x;
	else if (keysym == XK_Right
		&& data->map->map[data->map->start.y][data->map->start.x + 1] != WALL
		&& ++data->map->moves
		&& ft_dprintf(1, "You have moved %d time(s).\n", data->map->moves))
		++data->map->start.x;
}

/**
 * @brief The ft_on_keypress function handles the keypresses. It checks if the
 * player has pressed the escape key, and if so, it calls the ft_on_close
 * function. Otherwise, it calls the ft_handle_move function. It also handles
 * the win condition.
 * 
 * @param keysym 
 * @param data 
 * @return int 
 */
int	ft_on_keypress(int keysym, t_data *data)
{
	if (keysym == XK_Escape)
		ft_on_close(data);
	else
		ft_handle_move(keysym, data);
	if (data->map->map[data->map->start.y][data->map->start.x] == EXIT
		&& data->map->collectibles == 0)
	{
		ft_dprintf(1, "You win!\n");
		ft_dprintf(1, "Total moves: %d\n", data->map->moves);
		ft_on_close(data);
	}
	else if (data->map->map[data->map->start.y][data->map->start.x] == COLL)
	{
		--data->map->collectibles;
		data->map->map[data->map->start.y][data->map->start.x] = EMPT;
	}
	return (0);
}

/**
 * @brief The ft_on_close function frees the textures, mlx, and data, and then
 * exits the program.
 * 
 * @param data 
 * @return int 
 */
int	ft_on_close(t_data *data)
{
	ft_free_textures(data);
	ft_free_mlx(data);
	ft_free_data(data);
	exit(0);
	return (0);
}
