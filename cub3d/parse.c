/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juliencros <juliencros@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 09:54:31 by herbie            #+#    #+#             */
/*   Updated: 2024/03/21 17:33:01 by juliencros       ###   ########.fr       */
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
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define mapWidth 24
#define mapHeight 24

static bool	ft_parse_args(t_map *map);
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
	int	i;

	i = 0;
	printf(" ------ print data ------ \n");
	printf("NO = %p\n", data->map.no_img);
	printf("SO = %p\n", data->map.so_img);
	printf("WE = %p\n", data->map.we_img);
	printf("EA = %p\n", data->map.ea_img);
	printf("F = %ld\n", data->map.floor_hex);
	printf("C = %ld\n", data->map.ceiling_hex);
	printf("width = %d\n", data->map.width);
	printf("height = %d\n", data->map.height);
	printf("map: \n");
	while (i < data->map.height)
	{
		printf("%s", data->map.map[i]);
		i++;
	}
	printf(" ------------ \n");
	return (0);
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
	if (!ft_fill_texture(data, &data->map) || !ft_parse_args(&data->map))
		return (ft_err("ETXTUR"), false);
	if (!ft_init_map(&data->map) )
		return (ft_err("EMAP"), false);
	if (!ft_parse_map(data, &data->map))
		return (ft_err("EMAP2"), false);
	ft_print_data(data);
	close(data->fd); // TODO: check if ft_free or keep it here
	return (true);
}

static bool	ft_parse_args(t_map *map)
{
	// TODO: check if f and c exist and check if valid color
	// TODO: mlx take r, g, b, not one string.
	if (map->no_img == NULL || map->so_img == NULL
			|| map->we_img == NULL || map->ea_img == NULL
			|| map->floor_hex == -1 || map->ceiling_hex == -1)
			return (false);
	return (true);
}

static bool ft_parse_map(t_data *data, t_map *map)
{
	char **copy_map;
	int i;
	char **start;


	start = ft_split("N S W E", ' ', 0);
	i = 0;
	copy_map = ft_split(map->map_in_string + ft_count_nl(map), '\n', 1);
	if (copy_map == NULL)
		return (false);
	while (copy_map[i] != NULL)
	{
		if (ft_strchr_array(start, copy_map[i]) != -1)
		{
			map->start_row = i;
			map->start_col = ft_strchr_array(start, map->map[i]);
			map->row = i;
			map->col = map->start_col;
		}
		i++;
	}
	copy_map[map->row][map->col] = 'S';
	return (ft_resolve_map(data, copy_map));
}
