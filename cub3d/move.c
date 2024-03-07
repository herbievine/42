/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 15:59:56 by herbie            #+#    #+#             */
/*   Updated: 2024/03/07 13:38:06 by herbie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"
#include "move.h"
#include <math.h>
#include <stdbool.h>
#include <stdio.h>

// void	ft_move_player(t_data *data, int key)
// {
// 	double	move_step;
// 	double	new_player_x;
// 	double	new_player_y;

// 	move_step = data->player.move_speed;
// 	if (key == KEY_W)
// 	{
// 		new_player_x = data->player.x + cos(data->player.rotation_angle) * move_step;
// 		new_player_y = data->player.y + sin(data->player.rotation_angle) * move_step;
// 	}
// 	if (key == KEY_S)
// 	{
// 		new_player_x = data->player.x - cos(data->player.rotation_angle) * move_step;
// 		new_player_y = data->player.y - sin(data->player.rotation_angle) * move_step;
// 	}
// 	if (ft_is_wall(new_player_x, new_player_y, data))
// 	{
// 		data->player.x = new_player_x;
// 		data->player.y = new_player_y;
// 	}
// }

// bool	ft_move_player(t_data *data)
// {

// }

void ft_move_player_forward(t_data *data)
{
	int **map;
	t_player *p;

	printf("ft_move_player_forward\n");

	map = data->map2;
	p = &data->player;

	printf("Current pos: x: %f, y: %f\n", p->x, p->y);
	printf("Wants to move to: x: %f, y: %f\n", p->x + p->dx * p->movespeed, p->y + p->dy * p->movespeed);
	printf("X coords: x: %f, dx: %f, movespeed: %f\n", p->x, p->dx, p->movespeed);
	printf("Map value: %d\n", map[(int)(p->x + p->dx * p->movespeed)][(int)(p->y)]);

	if (map[(int)(p->x + p->dx * p->movespeed)][(int)(p->y)] == false)
		p->x += p->dx * p->movespeed;
	if (map[(int)(p->x)][(int)(p->y + p->dy * p->movespeed)] == false)
		p->y += p->dy * p->movespeed;
}

void ft_move_player_backward(t_data *data)
{
	int **map;
	t_player *p;

	printf("ft_move_player_backward\n");

	map = data->map2;
	p = &data->player;

	if (map[(int)(p->x - p->dx * p->movespeed)][(int)(p->y)] == false)
		p->x -= p->dx * p->movespeed;
	if (map[(int)(p->x)][(int)(p->y - p->dy * p->movespeed)] == false)
		p->y -= p->dy * p->movespeed;
}

void ft_move_player_left(t_data *data)
{
	t_player *p;

	printf("ft_move_player_left\n");

	p = &data->player;

	double oldDX = p->dx;
	p->dx = p->dx * cos(-p->rotspeed) - p->dy * sin(-p->rotspeed);
	p->dy = oldDX * sin(-p->rotspeed) + p->dy * cos(-p->rotspeed);
	double oldPlaneX = p->px;
	p->px = p->px * cos(-p->rotspeed) - p->py * sin(-p->rotspeed);
	p->py = oldPlaneX * sin(-p->rotspeed) + p->py * cos(-p->rotspeed);
}

void ft_move_player_right(t_data *data)
{
	t_player *p;

	printf("ft_move_player_right\n");

	p = &data->player;

	double oldDX = p->dx;
	p->dx = p->dx * cos(-p->rotspeed) - p->dy * sin(-p->rotspeed);
	p->dy = oldDX * sin(-p->rotspeed) + p->dy * cos(-p->rotspeed);
	double oldPlaneX = p->px;
	p->px = p->px * cos(-p->rotspeed) - p->py * sin(-p->rotspeed);
	p->py = oldPlaneX * sin(-p->rotspeed) + p->py * cos(-p->rotspeed);
}
