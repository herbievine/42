/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcros <jcros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 15:36:56 by juliencros        #+#    #+#             */
/*   Updated: 2024/04/08 14:57:50 by jcros            ###   ########.fr       */
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

/**
 * @brief create a new map in char ** format in the same with a
 * 	same width for all lines add fill with '0' the empty spaces.
 * 
 * @param map
 * @param with_err if true, the function will keep the characters
 * 	possible wrong characters and will not remove them. 
 * 	If false, the function will remove all characters that are not
 * 	'0' or '1' or "NEWS".
 * @return bool
 */
bool	ft_resize_map(t_map *map, bool with_err)
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
		if (new_map[i] == NULL)
			return (ft_free_array(new_map, i), false);
		ft_bzero(new_map[i], map->width + map->offset, '0');
		j = -1;
		while (++j < map->width + map->offset)
		{
			if (map->char_map[i] && (int)ft_strlen(map->char_map[i]) > j
				&& (ft_strchr("10NOWSE", map->char_map[i][j]) || with_err))
				new_map[i][j] = map->char_map[i][j];
		}
	}
	ft_free_array(map->char_map, map->height);
	map->char_map = new_map;
	return (true);
}

/**
 * @brief The function find amd define the offset and the width of the map
 * 	the width is the biggest line of the map and the offset is the number
 * 	of space before the first character of the biggest line.
 * @param map
 * @param parsed_line
 * @return bool
 */
bool	ft_define_offset_and_width(t_map *map, char **parsed_line)
{
	int	i;

	i = -1;
	map->width = 0;
	map->height = 0;
	while (map->char_map[++i])
	{
		map->height++;
		parsed_line[i] = ft_strtrim(map->char_map[i], "\t \n");
		if (parsed_line == NULL)
			return (false);
		if (map->width < (int)ft_strlen(parsed_line[i]))
		{
			map->width = ft_strlen(parsed_line[i]);
			map->offset = (ft_strlen(map->char_map[i]) - 1)
				- ft_strlen(parsed_line[i]);
		}
	}
	return (true);
}

/**
 * @brief The function initialize the map and will check if the
 * 	map is valid. At the end of the function, the map will be
 * 	resized in char ** and the offset and width will be defined. 
 * @param map
 * @return bool
 */
bool	ft_init_map(t_map *map)
{
	int		i;
	char	**parsed_line;
	int		count;

	i = -1;
	count = 0;
	while (map->map_in_string[++i] != '\0' && count < map->str_index)
		if (map->map_in_string[i] == '\n')
			count++;
	map->char_map = ft_split(map->map_in_string + i, '\n', 1);
	i = 0;
	if (map->char_map == NULL)
		return (false);
	while (map->char_map[i])
		i++;
	parsed_line = ft_calloc(sizeof(char *), (i + 1));
	if (parsed_line == NULL)
		return (false);
	if (!ft_define_offset_and_width(map, parsed_line))
		return (ft_free_array(parsed_line, -1), false);
	if (!ft_check_map(map, parsed_line) || !ft_resize_map(map, true))
		return (ft_free_array(parsed_line, -1), false);
	return (ft_free_array(parsed_line, -1), true);
}

/**
 * @brief The function will define the cardinal point of the map,
 * 	if where we are, we find a cardinal point, we will define
 * 	the direction of the player. and return true.
 * @param map
 * @param parsed_line
 * @param i
 * @param j
 * @return bool
 */
bool	ft_define_cardinal(t_map *map, char **parsed_line, int i, int j)
{
	if (parsed_line[i][j] == 'N' || parsed_line[i][j] == 'S'
				|| parsed_line[i][j] == 'W' || parsed_line[i][j] == 'E')
	{
		if (parsed_line[i][j] == 'N')
			map->start_dir = NORTH;
		else if (parsed_line[i][j] == 'S')
			map->start_dir = SOUTH;
		else if (parsed_line[i][j] == 'W')
			map->start_dir = WEST;
		else if (parsed_line[i][j] == 'E')
			map->start_dir = EAST;
		return (true);
	}
	return (false);
}

/**
 * @brief The function will define the cardinal point of the
 * 	map and check if there is vaild characters in the map.
 * 	If the function find more than one cardinal point, it will
 * 	return false. Same if the map is not valid.
 * @param map
 * @param parsed_line need a parsed line with only valid characters
 * 	characters, spaces and \ n are not valid characters.
 * @return bool
 */
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
		while (parsed_line[i] && parsed_line[i][j])
		{
			if (!ft_strchr(valid_char, parsed_line[i][j]))
				return (false);
			num_of_start += ft_define_cardinal(map, parsed_line, i, j);
			j++;
		}
		i++;
	}
	if (num_of_start != 1)
		return (false);
	return (true);
}
