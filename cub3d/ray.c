/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 14:12:20 by herbie            #+#    #+#             */
/*   Updated: 2024/04/01 10:15:47 by herbie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"
#include "window.h"
#include "pixels.h"
#include "textures.h"
#include "mlx/mlx.h"
#include <math.h>

/**
 * @brief The ft_init_ray function initializes the ray structure with the
 * necessary values to calculate the ray.
 *
 * @param ray
 * @param x
 * @param player
 */
static void	ft_init_ray(t_ray *ray, int x, t_player *player)
{
	ray->cx = 2 * x / (double)WIN_WIDTH - 1;
	ray->dx = player->dx + player->px * ray->cx;
	ray->dy = player->dy + player->py * ray->cx;
	ray->mx = (int)player->x;
	ray->my = (int)player->y;
	ray->ddx = fabs(1 / ray->dx);
	ray->ddy = fabs(1 / ray->dy);
}

/**
 * @brief The ft_calculate_step function calculates the step of the ray which is
 * then used to calculate the distance to the wall.
 *
 * @param ray
 * @param player
 */
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

/**
 * @brief The ft_calculate_wall_distance function calculates the distance to the
 * wall by calculating the distance to the next x or y side of the map.
 *
 * @param ray
 * @param map
 */
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
		if (map[ray->my][ray->mx] > 0)
			break ;
	}
	if (ray->side == 0)
		ray->wd = ray->sdx - ray->ddx;
	else
		ray->wd = ray->sdy - ray->ddy;
}

/**
 * @brief The ft_calculate_wall_height function calculates the height of the wall
 * and the draw start and draw end of the wall.
 * 
 * @param ray 
 * @param player 
 */
static void	ft_calculate_wall_height(t_ray *ray, t_player *player)
{
	ray->h = (int)(WIN_HEIGHT / ray->wd);
	ray->ds = -ray->h / 2 + WIN_HEIGHT / 2;
	if (ray->ds < 0)
		ray->ds = 0;
	ray->de = ray->h / 2 + WIN_HEIGHT / 2;
	if (ray->de >= WIN_HEIGHT)
		ray->de = WIN_HEIGHT - 1;
	if (ray->side == 0)
		ray->wx = player->y + ray->wd * ray->dy;
	else
		ray->wx = player->x + ray->wd * ray->dx;
	ray->wx -= floor(ray->wx);
}

/**
 * @brief The ft_cast_ray function handles the raycasting by initializing the
 * ray, calculating the step, calculating the wall distance, calculating the
 * wall height and finally, updating the pixel map.
 * 
 * @param data 
 * @param ray 
 */
void	ft_cast_ray(t_data *data, t_ray *ray)
{
	int	x;

	x = 0;
	while (x < WIN_WIDTH)
	{
		ft_init_ray(ray, x, &data->player);
		ft_calculate_step(ray, &data->player);
		ft_calculate_wall_distance(ray, data->map.map);
		ft_calculate_wall_height(ray, &data->player);
		ft_update_pixel_map(data, ray, x);
		x++;
	}
}
