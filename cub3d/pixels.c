/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixels.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcros <jcros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 16:25:30 by herbie            #+#    #+#             */
/*   Updated: 2024/03/26 15:45:24 by jcros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pixels.h"
#include "window.h"
#include "textures.h"
#include "mlx/mlx.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

bool	ft_create_texture_buffer_from_img(t_data *data,
		t_img *img, t_cardinal_direction dir)
{
	int	*pixels;
	int	i;
	int	j;

	pixels = malloc(sizeof(int) * img->width * img->height);
	if (!pixels)
		return (false);
	i = -1;
	while (++i < img->height)
	{
		j = -1;
		while (++j < img->width)
			pixels[i * img->width + j] = img->addr[i * img->line_length + j];
	}
	data->texture_buffer[dir] = pixels;
	return (true);
}

static t_cardinal_direction	ft_get_cardinal_direction(t_ray *ray)
{
	if (ray->side == 0)
	{
		if (ray->dx < 0)
			return (WEST);
		else
			return (EAST);
	}
	else
	{
		if (ray->dy > 0)
			return (SOUTH);
		else
			return (NORTH);
	}
}

bool	ft_create_pixel_map(t_data *data)
{
	int	i;

	data->pixels = malloc(sizeof(int *) * (WIN_HEIGHT + 1));
	if (!data->pixels)
		return (false);
	i = -1;
	while (++i < WIN_HEIGHT)
	{
		data->pixels[i] = malloc(sizeof(int) * WIN_WIDTH);
		if (!data->pixels[i])
			return (false);
	}
	return (true);
}

void	ft_update_pixel_map(t_data *data, t_ray *ray, int x)
{
	t_cardinal_direction	dir;
	int						y;
	int						text_x;
	int						tmp_pos;
	int						color;

	dir = ft_get_cardinal_direction(ray);
	text_x = (int)(ray->wd * TEXTURE_SIZE);
	if ((ray->side == 0 && ray->dx < 0) || (ray->side == 1 && ray->dy > 0))
		text_x = TEXTURE_SIZE - text_x - 1;
	tmp_pos = (ray->ds - WIN_HEIGHT / 2 + ray->h / 2)
		* (1.0 * TEXTURE_SIZE / ray->h);
	y = ray->ds;
	while (y < ray->de)
	{
		color = (data->texture_buffer)[dir][7];
		tmp_pos += 1.0 * TEXTURE_SIZE / ray->h;
		if (dir == NORTH || dir == EAST)
			color = (color >> 1) & 8355711;
		if (color > 0)
			data->pixels[y][x] = color;
		y++;
	}
}

void	ft_draw_pixel_map(t_data *data, t_ray ray)
{
	t_img	image;
	int		x;
	int		y;

	image.img = mlx_new_image(data->mlx_ptr, WIN_WIDTH, WIN_HEIGHT);
	if (image.img == NULL)
		return ;
	image.addr = (int *)mlx_get_data_addr(image.img, &image.bpp,
			&image.line_length, &image.endian);
	y = -1;
	while (++y < WIN_HEIGHT)
	{
		x = -1;
		while (++x < WIN_WIDTH)
		{
			if (data->pixels[y][x] > 0)
				image.addr[y * (image.line_length / 4) + x] = data->pixels[y][x];
			else if (y < WIN_HEIGHT / 2)
				image.addr[y * (image.line_length / 4) + x] = data->map.ceiling_hex;
			else if (y < WIN_HEIGHT -1)
				image.addr[y * (image.line_length / 4) + x] = data->map.floor_hex;
		}
	}
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, image.img, 0, 0);
}
