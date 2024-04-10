/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcros <jcros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 10:17:42 by jcros             #+#    #+#             */
/*   Updated: 2024/04/10 10:42:25 by jcros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "io.h"
#include "str.h"
#include "structs.h"
#include "free.h"
#include "split.h"
#include "error.h"
#include "textures.h"
#include "resolve_map.h"
#include "init.h"
#include "ints.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

static bool	ft_define_cardinal(t_map *map, char cardinal);

char	**ft_split_and_join_sep(const char *str, char sep)
{
	int		i;
	char	**split;
	char	*tmp;

	split = ft_split(str, sep);
	if (split == NULL)
		return (NULL);
	i = -1;
	while (split[++i])
	{
		tmp = split[i];
		split[i] = ft_strjoin(split[i], "\n");
		free(tmp);
		if (split[i] == NULL)
			return (ft_free_array(split, i), NULL);
	}
	return (split);
}

static bool	ft_verify_double_nl(t_map *map)
{
	int	i;

	i = -1;
	while (map->map_in_string[++i])
	{
		if (map->map_in_string[i] == '\n'
			&& map->map_in_string[i + 1]
			&& map->map_in_string[i + 1] == '\n'
			&& (ft_strchr(map->map_in_string + i + 1, '1')
				|| ft_strchr(map->map_in_string + i + 1, '0')))
			return (false);
	}
	return (true);
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
bool	ft_check_map(t_map *map, char **parsed_line)
{
	int		i;
	int		j;
	char	*valid_char;
	int		num_of_start;

	i = -1;
	num_of_start = 0;
	valid_char = "10NOWSE ";
	while (parsed_line && parsed_line[++i])
	{
		j = -1;
		while (parsed_line[i] && parsed_line[i][++j])
		{
			if (!ft_strchr(valid_char, parsed_line[i][j]))
				return (false);
			num_of_start += ft_define_cardinal(map, parsed_line[i][j]);
		}
	}
	if (num_of_start != 1 || !ft_verify_double_nl(map))
		return (false);
	return (true);
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
static bool	ft_define_cardinal(t_map *map, char cardinal)
{
	if (cardinal == 'N' || cardinal == 'S'
		|| cardinal == 'W' || cardinal == 'E')
	{
		if (cardinal == 'N')
			map->start_dir = NORTH;
		else if (cardinal == 'S')
			map->start_dir = SOUTH;
		else if (cardinal == 'W')
			map->start_dir = WEST;
		else if (cardinal == 'E')
			map->start_dir = EAST;
		return (true);
	}
	return (false);
}
