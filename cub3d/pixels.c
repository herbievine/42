/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixels.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 16:25:30 by herbie            #+#    #+#             */
/*   Updated: 2024/03/22 09:31:56 by herbie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pixels.h"
#include "window.h"
#include <stdbool.h>
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
		{
			pixels[i * img->width + j] = img->addr[i * img->line_length + j];
		}
	}
	data->texture_buffer[dir] = pixels;
	return (true);
}

static t_cardinal_direction	ft_get_cardinal_direction(t_ray ray)
{
	if (ray.side == 0)
	{
		if (ray.dx < 0)
			return (WEST);
		else
			return (EAST);
	}
	else
	{
		if (ray.dy > 0)
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

void	ft_update_pixel_map(t_data *data, t_ray ray, int x)
{
	t_cardinal_direction	dir;
	int						i;

	dir = ft_get_cardinal_direction(ray);
	i = -1;
	while (++i < ray.ds)
		data->pixels[i][x] = data->texture_buffer[NORTH][i % 64];
	while (i < ray.de)
	{
		data->pixels[i][x] = data->texture_buffer[dir][i % 64];
		i++;
	}
	while (i < WIN_HEIGHT)
	{
		data->pixels[i][x] = data->texture_buffer[SOUTH][i % 64];
		i++;
	}
}
