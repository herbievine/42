/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 16:00:58 by herbie            #+#    #+#             */
/*   Updated: 2023/05/07 15:15:51 by herbie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx/mlx.h"
#include "parse.h"
#include "structs.h"
#include "error.h"
#include "window.h"
#include <stdio.h>
#include <stdlib.h>

t_data	*ft_init(void)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
		return (ft_err(EUNKN), NULL);
	data->map = malloc(sizeof(t_map));
	if (!data->map)
		return (free(data), ft_err(EUNKN), NULL);
	data->map->map = NULL;
	data->map->width = 0;
	data->map->height = 0;
	data->map->start.x = 0;
	data->map->start.y = 0;
	data->map->collectibles = 0;
	data->map->exits = 0;
	data->map->entries = 0;
	data->map->moves = 0;
	return (data);
}

int	main(int argc, char *argv[])
{
	t_data	*data;

	if (argc != 2)
		ft_err(EIO);
	data = ft_init();
	ft_parse_map_or_throw(data, argv[1]);
	ft_init_window(data);
	return (0);
}
