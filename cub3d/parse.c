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

/**
 * @brief The ft_parse_map_or_throw function parses the map. It gathers 
 * information about the map, checks if the map is valid, and if so, returns
 * the map. Otherwise, it frees the data and exits with an error.
 * 
 * @param data 
 * @param map_path 
 */
void	ft_parse_map_or_throw(t_map *map, char *map_path)
{
	(void)map_path;
	// test map
	char local[8][8] = {
		{'1','1','1','1','1','1','1','1'},
		{'1','0','0','0','0','0','0','1'},
		{'1','0','0','0','0','1','0','1'},
		{'1','0','0','0','0','0','0','1'},
		{'1','0','1','0','0','0','0','1'},
		{'1','0','0','0','1','0','0','1'},
		{'1','0','0','0','0','0','0','1'},
		{'1','1','1','1','1','1','1','1'},	
	};

	// fill map
	int x = 0, y= 0, z = 8;
	while (x < z)
	{
		while (y < z)
		{
			map->map[x][y] = local[x][y];
			y++;
		}
		x++;
	}
}
