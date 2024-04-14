/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juliencros <juliencros@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 09:56:07 by herbie            #+#    #+#             */
/*   Updated: 2024/04/13 12:49:22 by juliencros       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "textures.h"
#include "pixels.h"
#include "structs.h"
#include "mlx/mlx.h"
#include "str.h"
#include "split.h"	
#include "error.h"
#include "init.h"
#include "free.h"
#include "ints.h"
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

static long	ft_char_to_rgb(char *str);
static void	ft_fill(char *line, t_map *map);

bool	ft_is_valid_rgb(char **splited)
{
	int	i;
	int	j;

	i = -1;
		while (splited[++i])
	{
		j = -1;
		while (splited[i][++j])
			if (!ft_strchr("0123456789", splited[i][j]))
				return (false);
		if (j < 1 || j > 3)
			return (false);
	}
	if (i != 3)
		return (false);
	return (true);
}

/**
 * @brief The ft_fill_map_config function fills the texture path. 
 * 	If it fails to find a texture, it returns false.
 * 
 * @param data 
 * @param map 
 * @return bool 
 */
bool	ft_fill_map_config(t_map *map)
{
	int		params;
	char	*buffer;

	params = 0;
	buffer = NULL;
	while (map->map_in_string[map->str_index]
		&& map->map_in_string[map->str_index + 1] != '\0' && params < 6)
	{
		buffer = ft_substr(map->map_in_string, map->str_index,
				ft_strchr(map->map_in_string + map->str_index, '\n')
				- map->map_in_string - map->str_index);
		if (buffer == NULL)
			return (false);
		if (ft_strchr_array((char *[7]){"NO", "SO", "WE", "EA", "F", "C", NULL},
			buffer) != -1)
		{
			(ft_fill(buffer, map), params++);
			map->str_index += ft_strchr(map->map_in_string + map->str_index,
					'\n') - map->map_in_string - map->str_index;
		}
		else
			map->str_index++;
		free(buffer);
	}
	return (true);
}

/**
 * @brief The ft_char_to_rgb function takes a string, checks it and returns
 * the hexadecimal value of the color as a long.
 * 
 * @param string
 * @return bool 
 */
static long	ft_char_to_rgb(char *str)
{
	char	**splited;
	int		*rgb_array;
	long	rgb;

	splited = ft_split(str, ',');
	if (splited == NULL)
		return (-1);
	if (ft_is_valid_rgb(splited) == false)
		return (ft_free_array(splited, -1), -1);
	rgb_array = malloc(sizeof(int) * 3);
	if (rgb_array == NULL)
		return (ft_free_array(splited, -1), -1);
	rgb_array[0] = ft_atoi(splited[0]);
	rgb_array[1] = ft_atoi(splited[1]);
	rgb_array[2] = ft_atoi(splited[2]);
	ft_free_array(splited, -1);
	if (rgb_array[0] < 0 || rgb_array[0] > 255 || rgb_array[1] < 0
		|| rgb_array[1] > 255 || rgb_array[2] < 0 || rgb_array[2] > 255)
		return (free(rgb_array), -1);
	rgb = (rgb_array[0] << 16) + (rgb_array[1] << 8) + rgb_array[2];
	return (free(rgb_array), rgb);
}

/**
 * @brief The ft_fill function fills the texture path.
 * 
 * @param line 
 * @param data 
 * @param map 
 * @return void
 */
static void	ft_fill(char *line, t_map *map)
{
	char	*parsed_line;

	if (line == NULL)
		return ;
	if (ft_strchr(line, 'C') || ft_strchr(line, 'F'))
		parsed_line = ft_strtrim(line + 2, " \t");
	else
		parsed_line = ft_strtrim(line + 3, " \t");
	if (ft_strncmp(line, "NO", 2) == 0 && ft_strschr(".xpm", line) != -1)
		map->path_texture[NORTH] = parsed_line;
	else if (ft_strncmp(line, "SO", 2) == 0 && ft_strschr(".xpm", line) != -1)
		map->path_texture[SOUTH] = parsed_line;
	else if (ft_strncmp(line, "WE", 2) == 0 && ft_strschr(".xpm", line) != -1)
		map->path_texture[WEST] = parsed_line;
	else if (ft_strncmp(line, "EA", 2) == 0 && ft_strschr(".xpm", line) != -1)
		map->path_texture[EAST] = parsed_line;
	else if (ft_strncmp(line, "F", 1) == 0)
		map->floor_hex = ft_char_to_rgb(parsed_line);
	else if (ft_strncmp(line, "C", 1) == 0)
		map->ceiling_hex = ft_char_to_rgb(parsed_line);
	if (ft_strchr(line, 'C') || ft_strchr(line, 'F'))
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
