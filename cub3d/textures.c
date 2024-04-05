/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcros <jcros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 09:56:07 by herbie            #+#    #+#             */
/*   Updated: 2024/04/05 17:52:33 by jcros            ###   ########.fr       */
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

static long	ft_char_to_hex(char *str);
static void	ft_fill(char *line, t_data *data, t_map *map);

/**
 * @brief The ft_fill_texture function fills the texture path. 
 * 	If it fails to find a texture, it returns false.
 * 
 * @param data 
 * @param map 
 * @return bool 
 */
bool	ft_fill_texture(t_data *data, t_map *map)
{
	int		params;
	char	**buffer_map;
	char	*buffer;

	params = 0;
	buffer_map = ft_split(data->map.map_in_string, '\n', 1);
	if (buffer_map == NULL)
		return (false);
	while (params < 6 && buffer_map[map->str_index] != NULL)
	{
		if (ft_strchr_array((char *[7]){"NO", "SO", "WE", "EA", "F", "C", NULL},
			buffer_map[map->str_index]) != -1)
		{
			buffer = ft_strtrim(buffer_map[map->str_index], "	 ");
			if (buffer == NULL)
				return (ft_free_array(buffer_map, -1), false);
			(ft_fill(buffer, data, map), free(buffer), params++);
		}
		map->str_index++;
	}
	(ft_free_array(buffer_map, -1));
	if (params != 6)
		return (false);
	return (true);
}

/**
 * @brief The ft_char_to_hex function takes a string, checks it and returns
 * the hexadecimal value of the color as a long.
 * 
 * @param string
 * @return bool 
 */
static long	ft_char_to_hex(char *str)
{
	char	**splited;
	int		*rgb_color;
	long	hex_color;

	splited = ft_split(str + 2, ',', 0);
	if (splited == NULL)
		return (-1);
	if (splited[0] == NULL || splited[1] == NULL
		|| splited[2] == NULL || splited[3] != NULL)
		return (ft_free_array(splited, -1), -1);
	if (ft_strlen(splited[0]) > 3
		|| ft_strlen(splited[1]) > 3 || ft_strlen(splited[2]) > 3)
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
	return (free(rgb_color), hex_color);
}

/**
 * @brief The ft_fill function fills the texture path.
 * 
 * @param line 
 * @param data 
 * @param map 
 * @return void
 */
static void	ft_fill(char *line, t_data *data, t_map *map)
{
	char	*parsed_line;

	if (line == NULL)
		return ;
	parsed_line = ft_strtrim(line, " 	\n");
	if (parsed_line == NULL)
		return ;
	if (ft_strncmp(line, "NO", 2) == 0 && ft_strschr(".xpm", line) != -1)
		map->path_texture[NORTH] = ft_strdup(ft_strchr(parsed_line, '.'));
	else if (ft_strncmp(line, "SO", 2) == 0 && ft_strschr(".xpm", line) != -1)
		map->path_texture[SOUTH] = ft_strdup(ft_strchr(parsed_line, '.'));
	else if (ft_strncmp(line, "WE", 2) == 0 && ft_strschr(".xpm", line) != -1)
		map->path_texture[WEST] = ft_strdup(ft_strchr(parsed_line, '.'));
	else if (ft_strncmp(line, "EA", 2) == 0 && ft_strschr(".xpm", line) != -1)
		map->path_texture[EAST] = ft_strdup(ft_strchr(parsed_line, '.'));
	else if (ft_strncmp(parsed_line, "F", 1) == 0)
		map->floor_hex = ft_char_to_hex(parsed_line);
	else if (ft_strncmp(parsed_line, "C", 1) == 0)
		map->ceiling_hex = ft_char_to_hex(parsed_line);
	free(parsed_line);
}

/**
 * @brief The ft_load_texture function loads the texture into the data struct.
 * If it fails to load a texture, it frees all the textures that were loaded
 * before and returns false.
 * 
 * @param data 
 * @return bool 
 */
bool	ft_load_textures(t_data *data)
{
	t_img	tmp;
	int		i;

	i = -1;
	while (++i < TEXTURE_COUNT)
	{
		tmp.img = mlx_xpm_file_to_image(data->mlx_ptr,
				data->map.path_texture[i], &tmp.width, &tmp.height);
		if (!tmp.img)
			return (false);
		tmp.addr = (int *)mlx_get_data_addr(tmp.img,
				&tmp.bpp, &tmp.line_len, &tmp.endian);
		if (!tmp.addr)
			return (mlx_destroy_image(data->mlx_ptr, tmp.img), false);
		if (!ft_create_texture_buffer_from_img(data, &tmp, i))
			return (mlx_destroy_image(data->mlx_ptr, tmp.img), false);
		mlx_destroy_image(data->mlx_ptr, tmp.img);
	}
	return (true);
}
