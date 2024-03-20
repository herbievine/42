/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 15:59:56 by herbie            #+#    #+#             */
/*   Updated: 2024/03/20 17:04:43 by herbie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"
#include "move.h"
#include <math.h>
#include <stdbool.h>
#include <stdio.h>

void	ft_move_player_forward(t_data *data)
{
	int			**map;
	t_player	*p;

	map = data->map2;
	p = &data->player;

	printf("CURRENTLY AT:\nmap[%f][%f] = %d\n", p->x, p->y, map[(int)p->x][(int)p->y]);
	printf("MOVING TO:\nmap[%d][%d] = \n", (int)(p->x + p->dx * p->movespeed), (int)(p->y));

	if (map[(int)(p->x + p->dx * p->movespeed)][(int)(p->y)] == 0)
		p->x += p->dx * p->movespeed;
	if (map[(int)(p->x)][(int)(p->y + p->dy * p->movespeed)] == 0)
		p->y += p->dy * p->movespeed;
}

void	ft_move_player_backward(t_data *data)
{
	int			**map;
	t_player	*p;

	map = data->map2;
	p = &data->player;

	if (map[(int)(p->x - p->dx * p->movespeed)][(int)(p->y)] == 0)
		p->x -= p->dx * p->movespeed;
	if (map[(int)(p->x)][(int)(p->y - p->dy * p->movespeed)] == 0)
		p->y -= p->dy * p->movespeed;
}

void	ft_move_player_left(t_data *data)
{
	t_player	*p;
	double		prev_dx;
	double		prev_px;

	p = &data->player;
	prev_dx = p->dx;
	prev_px = p->px;

	p->dx = p->dx * cos(p->rotspeed) - p->dy * sin(p->rotspeed);
	p->dy = prev_dx * sin(p->rotspeed) + p->dy * cos(p->rotspeed);
	p->px = p->px * cos(p->rotspeed) - p->py * sin(p->rotspeed);
	p->py = prev_px * sin(p->rotspeed) + p->py * cos(p->rotspeed);
}

void	ft_move_player_right(t_data *data)
{
	t_player	*p;
	double		prev_dx;
	double		prev_px;

	p = &data->player;
	prev_dx = p->dx;
	prev_px = p->px;

	p->dx = p->dx * cos(-p->rotspeed) - p->dy * sin(-p->rotspeed);
	p->dy = prev_dx * sin(-p->rotspeed) + p->dy * cos(-p->rotspeed);
	p->px = p->px * cos(-p->rotspeed) - p->py * sin(-p->rotspeed);
	p->py = prev_px * sin(-p->rotspeed) + p->py * cos(-p->rotspeed);
}
