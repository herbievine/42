/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juliencros <juliencros@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 15:59:56 by herbie            #+#    #+#             */
/*   Updated: 2024/03/23 17:25:12 by juliencros       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"
#include "move.h"
#include "math2.h"
#include <stdbool.h>
#include <stdio.h>
#include <math.h>

void	ft_move_player_forward(t_data *data)
{
	int			**map;
	t_player	*p;
	double		x;
	double		y;
	double		move_speed;

	map = data->map.map;
	p = &data->player;
	move_speed = ft_min(p->movespeed, 1.0);
	x = p->x + p->dx * move_speed;
	y = p->y + p->dy * move_speed;
	if (map[(int)(p->y)][(int)(x)] == 0)
		p->x += p->dx * move_speed;
	if (map[(int)(y)][(int)(p->x)] == 0)
		p->y += p->dy * move_speed;
}

void	ft_move_player_backward(t_data *data)
{
	int			**map;
	t_player	*p;
	double		x;
	double		y;
	double		move_speed;

	map = data->map.map;
	p = &data->player;
	move_speed = ft_min(p->movespeed, 1.0);
	x = p->x - p->dx * move_speed;
	y = p->y - p->dy * move_speed;
	if (map[(int)(p->y)][(int)(x)] == 0)
		p->x -= p->dx * move_speed;
	if (map[(int)(y)][(int)(p->x)] == 0)
		p->y -= p->dy * move_speed;
}

void	ft_move_player_right(t_data *data)
{
	t_player	*p;
	double		prev_dx;
	double		prev_px;
	double		rot_speed;

	p = &data->player;
	prev_dx = p->dx;
	prev_px = p->px;
	rot_speed = ft_min(p->rotspeed, 0.6);
	p->dx = p->dx * cos(rot_speed) - p->dy * sin(rot_speed);
	p->dy = prev_dx * sin(rot_speed) + p->dy * cos(rot_speed);
	p->px = p->px * cos(rot_speed) - p->py * sin(rot_speed);
	p->py = prev_px * sin(rot_speed) + p->py * cos(rot_speed);
}

void	ft_move_player_left(t_data *data)
{
	t_player	*p;
	double		prev_dx;
	double		prev_px;
	double		rot_speed;

	p = &data->player;
	prev_dx = p->dx;
	prev_px = p->px;
	rot_speed = ft_min(p->rotspeed, 0.6);
	p->dx = p->dx * cos(-rot_speed) - p->dy * sin(-rot_speed);
	p->dy = prev_dx * sin(-rot_speed) + p->dy * cos(-rot_speed);
	p->px = p->px * cos(-rot_speed) - p->py * sin(-rot_speed);
	p->py = prev_px * sin(-rot_speed) + p->py * cos(-rot_speed);
}
