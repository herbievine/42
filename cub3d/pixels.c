/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixels.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 16:25:30 by herbie            #+#    #+#             */
/*   Updated: 2024/03/30 15:13:12 by herbie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pixels.h"
#include "window.h"
#include "textures.h"
#include "mem.h"
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

	pixels = ft_calloc(sizeof(int), img->width * img->height);
	if (!pixels)
		return (false);
	i = -1;
	while (++i < img->height)
	{
		j = -1;
		while (++j < img->width)
			pixels[i * img->width + j] = img->addr[i * img->width + j];
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

	data->pixels = ft_calloc(sizeof(int *), WIN_HEIGHT + 1);
	if (!data->pixels)
		return (false);
	i = -1;
	while (++i < WIN_HEIGHT)
	{
		data->pixels[i] = ft_calloc(sizeof(int), WIN_WIDTH);
		if (!data->pixels[i])
		{
			while (--i >= 0)
				free(data->pixels[i]);
			free(data->pixels);
			return (false);
		}
	}
	return (true);
}

void	ft_update_pixel_map(t_data *data, t_ray *ray, int x)
{
	t_cardinal_direction	dir;
	int						tex_x;
	int						color;
	double					pos;
	double					step;

	dir = ft_get_cardinal_direction(ray);
	tex_x = (int)(ray->wx * TEXTURE_SIZE);
	if ((ray->side == 0 && ray->dx < 0) || (ray->side == 1 && ray->dy > 0))
		tex_x = TEXTURE_SIZE - tex_x - 1;
	step = 1.0 * TEXTURE_SIZE / ray->h;
	pos = (ray->ds - WIN_HEIGHT / 2 + ray->h / 2) * step;
	while (ray->ds < ray->de)
	{
		pos += step;
		color = (data->texture_buffer)[dir][TEXTURE_SIZE
			* ((int)pos & (TEXTURE_SIZE - 1)) + tex_x];
		if (dir == NORTH || dir == SOUTH)
			color = (color >> 1) & 0x7F7F7F;
		if (color > 0)
			data->pixels[ray->ds][x] = color;
		ray->ds++;
	}
}

void	ft_draw_pixel_map(t_data *data)
{
	t_img	img;
	int		x;
	int		y;

	img.img = mlx_new_image(data->mlx_ptr, WIN_WIDTH, WIN_HEIGHT);
	if (img.img == NULL)
		return ;
	img.addr = (int *)mlx_get_data_addr(img.img, &img.bpp,
			&img.line_len, &img.endian);
	y = -1;
	while (++y < WIN_HEIGHT)
	{
		x = -1;
		while (++x < WIN_WIDTH)
		{
			if (data->pixels[y][x] > 0)
				img.addr[y * (img.line_len / 4) + x] = data->pixels[y][x];
			else if (y < WIN_HEIGHT / 2)
				img.addr[y * (img.line_len / 4) + x] = data->map.ceiling_hex;
			else if (y < WIN_HEIGHT -1)
				img.addr[y * (img.line_len / 4) + x] = data->map.floor_hex;
		}
	}
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, img.img, 0, 0);
	mlx_destroy_image(data->mlx_ptr, img.img);
}
