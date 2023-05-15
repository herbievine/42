/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 09:54:31 by herbie            #+#    #+#             */
/*   Updated: 2023/05/15 11:03:25 by herbie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "io.h"
#include "str.h"
#include "structs.h"
#include "free.h"
#include "split.h"
#include "error.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

char	**ft_get_map(char *map_path);
void	ft_get_map_info(t_map *map);
t_bool	ft_check_basic_rules(t_map *map);
t_bool	ft_is_map_possible(t_map *map, int px, int py, t_flood *flood);

/**
 * @brief The ft_parse_map_or_throw function parses the map. It gathers 
 * information about the map, checks if the map is valid, and if so, returns
 * the map. Otherwise, it frees the data and exits with an error.
 * 
 * @param data 
 * @param map_path 
 */
void	ft_parse_map_or_throw(t_data *data, char *map_path)
{
	t_flood	*flood;
	char	**dup_map;

	data->map->map = ft_get_map(map_path);
	if (!data->map->map)
		return (ft_free_data(data), ft_err(EMAP));
	ft_get_map_info(data->map);
	flood = malloc(sizeof(t_flood));
	if (!flood)
		return (ft_free_data(data), ft_err(EUNKN));
	flood->collectibles = 0;
	flood->exits = 0;
	dup_map = ft_get_map(map_path);
	if (!dup_map)
		return (free(flood), ft_free_data(data), ft_err(EUNKN));
	if (!ft_check_basic_rules(data->map)
		|| !ft_is_map_possible(
			data->map, data->map->start.x, data->map->start.y, flood))
		return (free(flood), ft_free_array(dup_map, -1),
			ft_free_data(data), ft_err(EMAP));
	ft_free_array(data->map->map, -1);
	data->map->map = dup_map;
	free(flood);
}

/**
 * @brief The ft_get_map function reads the map file and returns the map as a
 * 2D array of characters.
 * 
 * @param map_path 
 * @return char** 
 */
char	**ft_get_map(char *map_path)
{
	char	*buffer;
	char	**map;
	int		fd;
	int		i;

	buffer = NULL;
	fd = open(map_path, O_RDONLY);
	if (ft_read(&buffer, fd) < 0)
		return (NULL);
	i = -1;
	while (buffer[++i])
		if (buffer[i] == '\n' && buffer[i + 1] == '\n')
			return (free(buffer), NULL);
	map = ft_split(buffer, '\n');
	free(buffer);
	return (map);
}

/**
 * @brief The ft_get_map_info function gathers information about the map.
 * 
 * @param map 
 */
void	ft_get_map_info(t_map *map)
{
	int	i;
	int	j;

	i = -1;
	while (map->map[++i])
	{
		if (i == 0)
			map->width = ft_strlen(map->map[i]);
		j = -1;
		while (map->map[i][++j])
		{
			if ((map->map[i][j] == EXIT && ++map->exits)
				|| (map->map[i][j] == STRT && ++map->entries)
				|| (map->map[i][j] == COLL && ++map->collectibles))
			{
			}
			if (map->map[i][j] == STRT)
				map->start = (t_start){j, i};
		}
	}
	map->height = i;
}

/**
 * @brief The ft_check_basic_rules function checks if the map respects the
 * basic rules imposed by the subject. If not, it returns false.
 * 
 * @param map 
 * @return t_bool 
 */
t_bool	ft_check_basic_rules(t_map *map)
{
	int	i;
	int	j;

	if (map->collectibles < 1 || map->exits != 1 || map->entries != 1
		|| map->width == map->height || map->width < 3 || map->height < 3)
		return (false);
	i = -1;
	while (map->map[++i])
	{
		j = -1;
		while (map->map[i][++j])
			if (((i == 0 || i == map->height - 1) && map->map[i][j] != WALL)
				|| ((j == 0 || j == map->width - 1) && map->map[i][j] != WALL)
				|| (map->map[i][j] != WALL && map->map[i][j] != EMPT
					&& map->map[i][j] != COLL && map->map[i][j] != STRT
					&& map->map[i][j] != EXIT))
				return (false);
		if ((int)ft_strlen(map->map[i]) != map->width)
			return (false);
	}
	return (true);
}

/**
 * @brief The ft_is_map_possible function checks if the map is possible by
 * flooding the map from the starting position. If the number of collectibles
 * and exits is the same as the number of collectibles and exits in the map,
 * it returns true. Otherwise, it returns false.
 * 
 * @param map 
 * @param px 
 * @param py 
 * @param flood 
 * @return t_bool 
 */
t_bool	ft_is_map_possible(t_map *map, int px, int py, t_flood *flood)
{
	if (flood->collectibles == map->collectibles && flood->exits == 1)
		return (true);
	if (map->map[py][px] == WALL)
		return (false);
	if (map->map[py][px] == COLL)
		flood->collectibles++;
	if (map->map[py][px] == EXIT)
		flood->exits++;
	map->map[py][px] = WALL;
	if (ft_is_map_possible(map, px + 1, py, flood) == true
		|| ft_is_map_possible(map, px - 1, py, flood) == true
		|| ft_is_map_possible(map, px, py + 1, flood) == true
		|| ft_is_map_possible(map, px, py - 1, flood) == true)
		return (true);
	return (false);
}
