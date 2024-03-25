/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juliencros <juliencros@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 09:56:07 by herbie            #+#    #+#             */
/*   Updated: 2024/03/23 19:29:06 by juliencros       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "textures.h"
#include "pixels.h"
#include "structs.h"
#include "mlx/mlx.h"
#include "str.h"
#include "split.h"	
#include "error.h"
#include "free.h"
#include "ints.h"
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

static long ft_char_to_hex(char *str);
static void	ft_fill(char *line, t_data *data, t_map *map);
static bool	ft_load_texture(t_data *data, t_cardinal_direction dir, char *path);

bool	ft_fill_texture(t_data *data, t_map *map)
{
	int		params;
	char	**buffer_map;
	char *buffer;
	char	**types;

	params = 0;
	types = ft_split("NO SO WE EA F C", ' ', 0);
	if (types == NULL)
		return (false);
	buffer_map = ft_split(data->map.map_in_string, '\n', 1);
	if (buffer_map == NULL)
		return (ft_free_array(types , -1), false);
	while (params < 6 && buffer_map[map->str_index] != NULL)
	{
		
		if (ft_strchr_array(types, buffer_map[map->str_index]) != -1)
		{
			buffer = ft_strtrim(buffer_map[map->str_index], "	 ");
			if (buffer == NULL)
				return (ft_free_array(types, -1), ft_free_array(buffer_map, -1), false);
			(ft_fill(buffer, data, map), free(buffer), params++);
		}
			map->str_index++;
	}
	(ft_free_array(types, -1), ft_free_array(buffer_map, -1));
		if (params != 6)
		return (false);
	return (true);
}

void	ft_apply_texture(t_data *data, int x)
{
	t_ray	ray;

	printf("ft_apply_texturefrom %d@ de %d\n", ray.ds, ray.de);

	ray = data->ray;
	while (ray.ds < ray.de)
	{
		mlx_pixel_put(data->mlx_ptr, data->win_ptr, x, ray.ds, 0xFF0000);
		ray.ds++;
	}
}
static long ft_char_to_hex(char *str)
{
	char **splited;
	int *rgb_color;
	long hex_color;

	splited = ft_split(str + 2, ',', 0);
	if (splited == NULL)
		return (-1);
	if (splited[0] == NULL || splited[1] == NULL || splited[2] == NULL || splited[3] != NULL)
		return (ft_free_array(splited, -1), -1);
	if (ft_strlen(splited[0]) > 3 || ft_strlen(splited[1]) > 3 || ft_strlen(splited[2]) > 3)
		return (ft_free_array(splited, -1), -1);
	rgb_color = malloc(sizeof(int) * 3);
	if (rgb_color == NULL)
		return (ft_free_array(splited, -1), -1);
	rgb_color[0] = ft_atoi(splited[0]);
	rgb_color[1] = ft_atoi(splited[1]);
	rgb_color[2] = ft_atoi(splited[2]);
	ft_free_array(splited, -1);
	if (rgb_color[0] < 0 || rgb_color[0] > 255 || rgb_color[1] < 0 
		|| rgb_color[1] > 255 || rgb_color[2] < 0 || rgb_color[2] > 255)
		return (free(rgb_color), -1);
	hex_color = (rgb_color[0] << 16) + (rgb_color[1] << 8) + rgb_color[2];
	free(rgb_color);
	return (hex_color);
}

static void	ft_fill(char *line, t_data *data, t_map *map)
{
	char	*parssed_line;

	if (line == NULL)
		return ;
	parssed_line = ft_strtrim(line, " 	\n");
	if (parssed_line == NULL)
		return ;
	if (ft_strncmp(line, "NO", 2) == 0 && ft_strschr(".xpm", line) != -1)
	{
		map->path_texture[NORTH] = ft_strdup(ft_strchr(parssed_line, '.'));
		// ft_load_texture(data, NORTH, ft_strchr(parssed_line, '.'));
	}
	else if (ft_strncmp(line, "SO", 2) == 0 && ft_strschr(".xpm", line) != -1)
	{
		map->path_texture[SOUTH] = ft_strdup(ft_strchr(parssed_line, '.'));
		// ft_load_texture(data, SOUTH, ft_strchr(parssed_line, '.'));
	}
	else if (ft_strncmp(line, "WE", 2) == 0 && ft_strschr(".xpm", line) != -1)
	{
		map->path_texture[WEST] = ft_strdup(ft_strchr(parssed_line, '.'));
		// ft_load_texture(data, WEST, ft_strchr(parssed_line, '.'));
	}
	else if (ft_strncmp(line, "EA", 2) == 0 && ft_strschr(".xpm", line) != -1)
	{
		map->path_texture[EAST] = ft_strdup(ft_strchr(parssed_line, '.'));
		// ft_load_texture(data, EAST, ft_strchr(parssed_line, '.'));
	}
	else if (ft_strncmp(parssed_line, "F", 1) == 0)
		map->floor_hex = ft_char_to_hex(parssed_line);
	else if (ft_strncmp(parssed_line, "C", 1) == 0)
		map->ceiling_hex = ft_char_to_hex(parssed_line);
	free(parssed_line);
}

 bool	ft_load_texture(t_data *data, t_cardinal_direction dir, char *path)
{
	data->textures[dir].img = mlx_xpm_file_to_image(
			data->mlx_ptr,
			path,
			&data->textures[dir].width,
			&data->textures[dir].height);
	if (!data->textures[dir].img)
		return (false);
	return (true);
}
#define TEXTURES 4

// /**
//  * @brief The ft_load_texture function loads the texture into the data struct.
//  * If it fails to load a texture, it frees all the textures that were loaded
//  * before and returns false.
//  * 
//  * @param data 
//  * @return bool 
//  */
bool	ft_load_textures(t_data *data)
{
	t_img	tmp;
	int		i;

	i = -1;
	while (++i < TEXTURES)
	{
		tmp.img = mlx_xpm_file_to_image(data->mlx_ptr,
				data->map.path_texture[i], &tmp.width, &tmp.height);
		if (!tmp.img)
			return (false);
		tmp.addr = mlx_get_data_addr(tmp.img,
				&tmp.bpp, &tmp.line_length, &tmp.endian);
		if (!tmp.addr)
			return (false);
		if (!ft_create_texture_buffer_from_img(data, &tmp, i))
			return (false);
		// mlx_destroy_image(data->mlx_ptr, tmp.img);
	}
	return (true);
}
