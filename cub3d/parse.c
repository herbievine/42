/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcros <jcros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 09:54:31 by herbie            #+#    #+#             */
/*   Updated: 2024/03/31 17:18:45 by jcros            ###   ########.fr       */
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

#define mapWidth 24
#define mapHeight 24

static bool	ft_parse_args(t_data *data);
static bool ft_parse_map(t_data *data, t_map *map);

int worldMap[mapWidth][mapHeight]=
{
  {4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,7,7,7,7,7,7,7,7},
  {4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7,0,0,0,0,0,0,7},
  {4,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7},
  {4,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7},
  {4,0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,7,0,0,0,0,0,0,7},
  {4,0,4,0,0,0,0,5,5,5,5,5,5,5,5,5,7,7,0,7,7,7,7,7},
  {4,0,5,0,0,0,0,5,0,5,0,5,0,5,0,5,7,0,0,0,7,7,7,1},
  {4,0,6,0,0,0,0,5,0,0,0,0,0,0,0,5,7,0,0,0,0,0,0,8},
  {4,0,7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7,7,7,1},
  {4,0,8,0,0,0,0,5,0,0,0,0,0,0,0,5,7,0,0,0,0,0,0,8},
  {4,0,0,0,0,0,0,5,0,0,0,0,0,0,0,5,7,0,0,0,7,7,7,1},
  {4,0,0,0,0,0,0,5,5,5,5,0,5,5,5,5,7,7,7,7,7,7,7,1},
  {6,6,6,6,6,6,6,6,6,6,6,0,6,6,6,6,6,6,6,6,6,6,6,6},
  {8,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4},
  {6,6,6,6,6,6,0,6,6,6,6,0,6,6,6,6,6,6,6,6,6,6,6,6},
  {4,4,4,4,4,4,0,4,4,4,6,0,6,2,2,2,2,2,2,2,3,3,3,3},
  {4,0,0,0,0,0,0,0,0,4,6,0,6,2,0,0,0,0,0,2,0,0,0,2},
  {4,0,0,0,0,0,0,0,0,0,0,0,6,2,0,0,5,0,0,2,0,0,0,2},
  {4,0,0,0,0,0,0,0,0,4,6,0,6,2,0,0,0,0,0,2,2,0,2,2},
  {4,0,6,0,6,0,0,0,0,4,6,0,0,0,0,0,5,0,0,0,0,0,0,2},
  {4,0,0,5,0,0,0,0,0,4,6,0,6,2,0,0,0,0,0,2,2,0,2,2},
  {4,0,6,0,6,0,0,0,0,4,6,0,6,2,0,0,5,0,0,2,0,0,0,2},
  {4,0,0,0,0,0,0,0,0,4,6,0,6,2,0,0,0,0,0,2,0,0,0,2},
  {4,4,4,4,4,4,4,4,4,4,1,1,1,2,2,2,2,2,2,3,3,3,3,3}
};

// void	ft_init_map(t_data *data)
// {
// 	// allocate memory for map int**map2
// 	data->map2 = malloc(mapHeight * sizeof(int*));
// 	for (int i = 0; i < mapHeight; i++)
// 	{
// 		(data->map2)[i] = malloc(mapWidth * sizeof(int));
// 	}

// 	// fill map
// 	int x = 0, y= 0;
// 	while (x < mapWidth)
// 	{
// 		y = 0;
// 		while (y < mapHeight)
// 		{
// 			data->map2[x][y] = worldMap[x][y];
// 			y++;
// 		}
// 		x++;
// 	}

// }

// void	ft_print_map(t_data data)
// {
// 	int x = 0, y = 0;
// 	printf("MAP:\n\n");
// 	while (x < mapWidth)
// 	{
// 		y = 0;
// 		while (y < mapHeight)
// 		{
// 			printf("%d", data.map2[x][y]);
// 			y++;
// 		}
// 		printf("\n");
// 		x++;
// 	}
// }

/**
 * @brief The ft_parse_map_or_throw function parses the map. It gathers 
 * information about the map, checks if the map is valid, and if so, returns
 * the map. Otherwise, it frees the data and exits with an error.
 * 
 * @param data 
 * @param map_path 
 */
// void	ft_parse_map_or_throw(int ***map, char *map_path)
// {
// 	(void)map_path;
// 	// test map

// 	// allocate memory for map int**map2
// 	data->map = malloc(mapHeight * sizeof(int*));
// 	for (int i = 0; i < mapHeight; i++)
// 	{
// 		(data->map)[i] = malloc(mapWidth * sizeof(int));
// 	}

// 	// fill map
// 	int x = 0, y= 0;
// 	while (x < mapWidth)
// 	{
// 		y = 0;
// 		while (y < mapHeight)
// 		{
// 			map[x][y] = worldMap[x][y];
// 			y++;
// 		}
// 		x++;
// 	}
// }

int	ft_print_data(t_data *data)
{
	printf(" ------ print data ------ \n");
	printf("NO = %p\n", data->textures[0].img);
	printf("SO = %p\n", data->textures[1].img);
	printf("WE = %p\n", data->textures[2].img);
	printf("EA = %p\n", data->textures[3].img);
	printf("F = %ld\n", data->map.floor_hex);
	printf("C = %ld\n", data->map.ceiling_hex);
	printf("width = %d\n", data->map.width);
	printf("height = %d\n", data->map.height);
	printf("offset = %d\n", data->map.offset);
	printf("map: \n");
	int i = 0;
	int j = 0;
	while (i < data->map.height)
	{
		j = 0;
		while (j < data->map.width + data->map.offset)
		{
			printf("%d", data->map.map[i][j]);
			j++;
		}
		printf("\n");
		i++;
	}	
	printf(" ------------ \n");
	return (0);
}

static bool ft_to_int_map(t_map *map)
{
	int i;
	int j;

	i = -1;
	map->map = malloc(map->height * sizeof(int*));
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
	if (argv[1][ft_strlen(argv[1]) - 3] != 'c' || argv[1][ft_strlen(argv[1]) - 2] != 'u' 
		|| argv[1][ft_strlen(argv[1]) - 1] != 'b' || argv[1][ft_strlen(argv[1]) - 4] != '.')
		return (ft_err("EFILE"), false);
	data->fd = open(argv[1], O_RDONLY);
	if (data->fd < 0)
	{
		ft_err("ENOENT");
		exit(0);
	}
	ft_read(&data->map.map_in_string, data->fd);
	if (data->map.map_in_string == NULL)
		return (ft_err("EMAP"), false);
	if (!ft_fill_texture(data, &data->map) || !ft_parse_args(data))
		return (ft_err("ETXTUR"), false);
	if (!ft_init_map(&data->map))
		return (ft_err("EMAP"), false);
	if (!ft_parse_map(data, &data->map))
		return (ft_err("EMAP2"), false);
		if (!ft_to_int_map(&data->map))
		return (ft_err("EMAP3"), false);
	if (!ft_load_textures(data))
		return (ft_err("ETXTUR2"), false);
	// ft_print_data(data);
	return (true);
}

static bool	ft_parse_args(t_data *data)
{
	// if (data->textures[0].img == NULL || data->textures[1].img == NULL 
	// 	|| data->textures[2].img == NULL || data->textures[3].img == NULL 
	
	if ( data->map.floor_hex == -1 || data->map.ceiling_hex == -1)
			return (false);
	return (true);
}

static bool ft_parse_map(t_data *data, t_map *map)
{
	char **copy_map;
	int i;
	char **start;


	start = ft_split("N S W E", ' ', 0);
	if (start == NULL)
		return (false);
	i = 0;
	// copy_map = ft_split(map->map_in_string + ft_count_nl(map), '\n', 1);
	copy_map  = ft_calloc(map->height + 1, sizeof(char *));
	while (i < map->height)
	{
		copy_map[i] = ft_strdup(map->char_map[i]);
		i++;
	}
	i = 0;
	if (copy_map == NULL)
		return (ft_free_array(start, 5), false);
	while (copy_map[i] != NULL)
	{
		if (ft_strchr_array(start, copy_map[i]) != -1)
		{
			map->start_row = i;
			map->start_col = ft_strchr_array(start, map->char_map[i]);
			map->row = i;
			map->col = map->start_col;
		}
		i++;
	}
	copy_map[map->row][map->col] = 'S';
	ft_free_array(start, 5);
	if (!ft_resolve_map(data, copy_map))
		return (ft_free_array(copy_map, -1), false);
	ft_resize_map(map, false);
	return (ft_free_array(copy_map, -1), true);
}
