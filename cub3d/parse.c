/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcros <jcros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 09:54:31 by herbie            #+#    #+#             */
/*   Updated: 2024/04/02 14:26:10 by jcros            ###   ########.fr       */
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

static bool	ft_parse_args(t_data *data);
static bool	ft_parse_map(t_data *data, t_map *map);
static bool	ft_to_int_map(t_map *map);

static bool	ft_to_int_map(t_map *map)
{
	int	i;
	int	j;

	i = -1;
	map->map = malloc(map->height * sizeof(int *));
	if (map->map == NULL)
		return (false);
	i = -1;
	while (++i < map->height)
	{
		map->map[i] = malloc((map->width + map->offset) * sizeof(int));
		if (map->map[i] == NULL)
			return (ft_free_array_int(map->map, i - 1), false);
		j = -1;
		while (map->char_map[i][++j])
		{
			if (ft_strchr("01", map->char_map[i][j]))
				map->map[i][j] = map->char_map[i][j] - '0';
			else 
				map->map[i][j] = 0;
		}
	}
	return (true);
}

bool	ft_fill_and_parse_data(char *argv[], t_data *data)
{
	if (argv[1][ft_strlen(argv[1]) - 3] != 'c'
		|| argv[1][ft_strlen(argv[1]) - 2] != 'u' 
		|| argv[1][ft_strlen(argv[1]) - 1] != 'b'
		|| argv[1][ft_strlen(argv[1]) - 4] != '.')
		return (ft_err("EFILE"), false);
	data->fd = open(argv[1], O_RDONLY);
	if (data->fd < 0)
	{
		ft_err("ENOENT");
		return (false);
	}
	ft_read(&data->map.map_in_string, data->fd);
	if (data->map.map_in_string == NULL)
		return (ft_err("EMAP"), false);
	if (!ft_fill_texture(data, &data->map) || !ft_parse_args(data))
		return (ft_err("ETXTUR"), false);
	if (!ft_init_map(&data->map) || !ft_parse_map(data, &data->map)
		|| !ft_to_int_map(&data->map))
		return (ft_err("EMAP"), false);
	if (!ft_load_textures(data))
		return (ft_err("ETXTUR2"), false);
	return (true);
}

static bool	ft_parse_args(t_data *data)
{
	if (data->map.floor_hex == -1 || data->map.ceiling_hex == -1)
		return (false);
	return (true);
}

static bool	ft_find_start(t_map *map, char **copy_map)
{
	char	**start;
	int		i;

	start = ft_split("N S W E", ' ', 0);
	if (start == NULL)
		return (false);
	i = -1;
	while (copy_map[++i] != NULL)
	{
		if (ft_strchr_array(start, copy_map[i]) != -1)
		{
			map->start_row = i;
			map->start_col = ft_strchr_array(start, map->char_map[i]);
		}
	}
	return (ft_free_array(start, 5), true);
}

static bool	ft_parse_map(t_data *data, t_map *map)
{
	char	**copy_map;
	int		i;
	char	**start;

	i = -1;
	copy_map = ft_calloc(map->height + 1, sizeof(char *));
	if (copy_map == NULL)
		return (false);
	while (++i < map->height)
		copy_map[i] = ft_strdup(map->char_map[i]);
	if (copy_map == NULL)
		return (ft_free_array(start, 5), false);
	if (!ft_find_start(map, copy_map))
		return (ft_free_array(copy_map, -1), false);
	if (!ft_resolve_map(data, copy_map))
		return (ft_free_array(copy_map, -1), false);
	return (ft_free_array(copy_map, -1), ft_resize_map(map, false));
}
