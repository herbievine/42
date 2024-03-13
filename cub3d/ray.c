/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 14:12:20 by herbie            #+#    #+#             */
/*   Updated: 2024/03/13 14:12:20 by herbie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"
#include "window.h"
#include "textures.h"
#include <math.h>

static void	ft_init_ray(t_ray *ray, int x, t_player *player)
{
	ray->cx = 2 * x / (double)WIN_WIDTH - 1;
	ray->dx = player->dx + player->px * ray->cx;
	ray->dy = player->dy + player->py * ray->cx;
	ray->mx = (int)player->x;
	ray->my = (int)player->y;
	ray->sx = 0;
	ray->sy = 0;
	ray->sdx = 0;
	ray->sdy = 0;
	ray->ddx = fabs(1 / ray->dx);
	ray->ddy = fabs(1 / ray->dy);
	ray->wd = 0;
	ray->side = 0;
	ray->h = 0;
	ray->ds = 0;
	ray->de = 0;
}

static void	ft_calculate_step(t_ray *ray, t_player *player)
{
	if (ray->dx < 0)
	{
		ray->sx = -1;
		ray->sdx = (player->x - ray->mx) * ray->ddx;
	}
	else
	{
		ray->sx = 1;
		ray->sdx = (ray->mx + 1.0 - player->x) * ray->ddx;
	}
	if (ray->dy < 0)
	{
		ray->sy = -1;
		ray->sdy = (player->y - ray->my) * ray->ddy;
	}
	else
	{
		ray->sy = 1;
		ray->sdy = (ray->my + 1.0 - player->y) * ray->ddy;
	}
}

static void	ft_calculate_wall_distance(t_ray *ray, int **map)
{
	while (42)
	{
		if (ray->sdx < ray->sdy)
		{
			ray->sdx += ray->ddx;
			ray->mx += ray->sx;
			ray->side = 0;
		}
		else
		{
			ray->sdy += ray->ddy;
			ray->my += ray->sy;
			ray->side = 1;
		}
		if (map[ray->my][ray->mx] != '0')
			break ;
	}
	if (ray->side == 0)
		ray->wd = ray->sdx - ray->ddx;
	else
		ray->wd = ray->sdy - ray->ddy;
}

static void	ft_calculate_wall_height(t_ray *ray)
{
	ray->h = (int)(WIN_HEIGHT / ray->wd);
	ray->ds = -ray->h / 2 + WIN_HEIGHT / 2;
	if (ray->ds < 0)
		ray->ds = 0;
	ray->de = ray->h / 2 + WIN_HEIGHT / 2;
	if (ray->de >= WIN_HEIGHT)
		ray->de = WIN_HEIGHT - 1;
}

void	ft_cast_ray(t_data *data)
{
	t_ray	ray;
	int				x;

	ray = data->ray;
	x = 0;
	while (x < WIN_WIDTH)
	{
		ft_init_ray(&ray, x, &data->player);
		ft_calculate_step(&ray, &data->player);
		ft_calculate_wall_distance(&ray, data->map2);
		ft_calculate_wall_height(&ray);
		ft_apply_texture(data, x);
		x++;
	}
}
