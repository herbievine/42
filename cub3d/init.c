/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juliencros <juliencros@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 15:36:56 by juliencros        #+#    #+#             */
/*   Updated: 2024/03/27 18:49:59 by juliencros       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "init.h"
#include "get_line.h"
#include <stdlib.h>
#include <fcntl.h>
#include "mlx.h"
#include "error.h"
#include "str.h"
#include "free.h"
#include "io.h"
#include "split.h"
#include "ints.h"
#include "textures.h"
#include <stdbool.h>

static bool	ft_check_map(t_map *map, char **parsed_line);

void	ft_init(t_data *data)
{
	data->map.map_in_string = NULL;
	data->map.char_map = NULL;
	data->map.map = NULL;
	data->map.no_img = NULL;
	data->map.so_img = NULL;
	data->map.we_img = NULL;
	data->map.ea_img = NULL;
	data->map.floor_hex = -1;
	data->map.ceiling_hex = -1;
	data->map.width = 0;
	data->map.height = 0;
	data->map.row = 0;
	data->map.col = 0;
	data->map.index = 'a';
	data->map.start_row = 0;
	data->map.start_col = 0;
	data->map.str_index = 0;
	data->map.offset = 0;
	data->mlx_ptr = NULL;
	data->fd = 0;
	data->map.path_texture = malloc(sizeof(char *) * 4);
	if (data->map.path_texture == NULL)
		ft_err("Malloc failed");
	// data->map.path_texture[5] = NULL;
	data->mlx_ptr = mlx_init();
}

int	ft_count_nl(t_map *map)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (map->map_in_string[i] != '\0' &&  count < map->str_index)
	{
		if (map->map_in_string[i] == '\n')
			count++;
		i++;
	}
	return (i);
}

// bool ft_resize_end(t_map *map, int start_col)
// {
// 	int row;
// 	int col;

// 	row = map->height;
// 	while (map->map[row])
// 	{
// 		col = 0;
// 		while (map->map[row][col] != '\0')
// 		{
// 			if (col < start_col)
// 				map->map[row][col] = '0';
// 			col++;
// 		}
// 		row++;
// 	}
// 	return (true);
// }

bool ft_resize_map(t_map *map)
{
	int		i;
	int		j;
	char	**new_map;

	i = -1;
	new_map = ft_calloc(sizeof(char *), (map->height + 1));
	if (new_map == NULL)
		return (false);
	while (++i < map->height)
	{
		new_map[i] = ft_calloc(sizeof(char), (map->width + map->offset + 1));
		ft_bzero(new_map[i], map->width + map->offset, '0');
		if (new_map[i] == NULL)
			return (ft_free_array(new_map, i - 1), false);
		j = -1;
		while (++j < map->width + map->offset)
		{
			if (map->char_map[i][j] && ft_strchr("10NOWSE", map->char_map[i][j]))
				new_map[i][j] = map->char_map[i][j];
			else
				new_map[i][j] = '0';
		}
		new_map[i][j - 1] = '\n';
		new_map[i][j] = '\0';
	}
	new_map[i] = NULL;
	ft_free_array(map->char_map, map->height);
	map->char_map = new_map;
	return (true);
}	

bool	ft_init_map(t_map *map)
{
	int		i;
	char	**parsed_line;

	i = 0;
	map->char_map = ft_split(map->map_in_string + ft_count_nl(map), '\n', 1);
	if (map->char_map == NULL)
		return (false);
	while (map->char_map[i])
		i++;
	parsed_line = malloc(sizeof(char *) * (i + 1));
	if (parsed_line == NULL)
		return (false);
	i = -1;
	while (map->char_map[++i])
	{
		map->height++;
		parsed_line[i] = ft_strtrim(map->char_map[i], "\t \n");
		if (parsed_line == NULL)
			return (ft_free_array(parsed_line, i - 1) ,false);
		if (map->width < (int)ft_strlen(parsed_line[i]))
		{
			map->width = ft_strlen(parsed_line[i]);
			map->offset = (ft_strlen(map->char_map[i]) - 1) - ft_strlen(parsed_line[i]);
		}
	}
	parsed_line[i] = NULL;
	if (!ft_check_map(map, parsed_line) || !ft_resize_map(map))
		return (ft_free_array(parsed_line, i),  false);
	return (ft_free_array(parsed_line, i), true);
}


static bool	ft_check_map(t_map *map, char **parsed_line)
{
	int		i;
	int		j;
	char	*valid_char;
	int		num_of_start;

	i = 0;
	num_of_start = 0;
	valid_char = "10NOWSE ";
	while (parsed_line && parsed_line[i])
	{
		j = 0;
		while (parsed_line[i]&& parsed_line[i][j])
		{
			if (!ft_strchr(valid_char, parsed_line[i][j]))
				return (printf("parsed_line[%d][%d] = %c\n", i, j, parsed_line[i][j]),false);
			if (parsed_line[i][j] == 'N' || parsed_line[i][j] == 'S' || parsed_line[i][j] == 'W' || parsed_line[i][j] == 'E')
			{
				map->start_dir = parsed_line[i][j] == 'N' ? NORTH : parsed_line[i][j] == 'S'
					? SOUTH : parsed_line[i][j] == 'W' ? WEST : EAST;
				num_of_start++;
			}
			j++;
		}
		i++;
	}
	if (num_of_start != 1)
		return (false);
	return (true);
}
