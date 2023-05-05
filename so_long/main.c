/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 16:00:58 by herbie            #+#    #+#             */
/*   Updated: 2023/05/05 18:07:05 by herbie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx/mlx.h"
#include "parse.h"
#include "structs.h"
#include "error.h"
#include <stdlib.h>

void	ft_init(t_map *map)
{
	map->map = NULL;
	map->width = 0;
	map->height = 0;
	map->collectibles = 0;
	map->exits = 0;
	map->entries = 0;
	map->moves = 0;
	map->is_valid = false;
	map->is_finished = false;
}

int	main(int argc, char *argv[])
{
	t_map	*map;

	if (argc != 2)
		ft_err(EIO, NULL);
	map = malloc(sizeof(t_map));
	if (!map)
		ft_err(EUNKN, NULL);
	ft_init(map);
	ft_parse_map_or_throw(map, argv[1]);
}
