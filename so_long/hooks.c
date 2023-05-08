/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 14:33:04 by herbie            #+#    #+#             */
/*   Updated: 2023/05/07 19:12:19 by herbie           ###   ########.fr       */
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

void	handle_move(int keysym, t_data *data)
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

int	on_keypress(int keysym, t_data *data)
{
	if (keysym == XK_Escape)
		on_destroy(data);
	else if (keysym == XK_Up || keysym == XK_Down
		|| keysym == XK_Left || keysym == XK_Right)
		handle_move(keysym, data);
	if (data->map->map[data->map->start.y][data->map->start.x] == EXIT
		&& data->map->collectibles == 0)
	{
		ft_dprintf(1, "You win!\n");
		ft_dprintf(1, "Total moves: %d\n", data->map->moves);
		on_destroy(data);
	}
	else if (data->map->map[data->map->start.y][data->map->start.x] == COLL)
	{
		--data->map->collectibles;
		data->map->map[data->map->start.y][data->map->start.x] = EMPT;
	}
	return (0);
}

int	on_destroy(t_data *data)
{
	ft_free_textures(data);
	ft_free_mlx(data);
	ft_free_data(data);
	exit(0);
	return (0);
}
