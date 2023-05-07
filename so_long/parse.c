/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 09:54:31 by herbie            #+#    #+#             */
/*   Updated: 2023/05/07 10:25:38 by herbie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "io.h"
#include "str.h"
#include "structs.h"
#include "split.h"
#include "error.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

void	ft_get_map_info(t_map *map);
t_bool	ft_check_basic_rules(t_map *map);
t_bool	ft_is_map_possible(t_map *map, int px, int py, t_flood *flood);

void	ft_parse_map_or_throw(t_map *map, char *map_path)
{
	t_flood	*flood;
	char	*buffer;
	int		fd;

	buffer = NULL;
	fd = open(map_path, O_RDONLY);
	if (fd < 0 || ft_read(&buffer, fd) < 0)
		ft_err(EUNKN, map);
	map->map = ft_split(buffer, '\n');
	free(buffer);
	if (!map->map)
		ft_err(EMAP, map);
	ft_get_map_info(map);
	flood = (t_flood *)malloc(sizeof(t_flood));
	if (!flood)
		ft_err(EUNKN, map);
	if (!ft_check_basic_rules(map)
		|| !ft_is_map_possible(map, map->start.x, map->start.y, flood))
	{
		free(flood);
		ft_err(EMAP, map);
	}
	free(flood);
}

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
				;
			if (map->map[i][j] == STRT)
				map->start = (t_start){j, i};
		}
	}
	map->height = i;
}

t_bool	ft_check_basic_rules(t_map *map)
{
	int	i;
	int	j;

	if (map->collectibles < 1 || map->exits != 1 || map->entries != 1
		|| map->width == map->height)
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

t_bool	ft_is_map_possible(t_map *map, int px, int py, t_flood *flood)
{
	if (!flood->collectibles && !flood->exits)
	{
		flood->collectibles = 0;
		flood->exits = 0;
	}
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
