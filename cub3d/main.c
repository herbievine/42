/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcros <jcros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 16:00:58 by herbie            #+#    #+#             */
/*   Updated: 2024/04/04 12:02:39 by jcros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx/mlx.h"
#include "structs.h"
#include "parse.h"
#include "error.h"
#include "window.h"
#include "player.h"
#include "init.h"
#include "free.h"
#include "mem.h"
#include <stdio.h>
#include <stdlib.h>

static int	ft_print_data(t_data *data)
{
	int	i;
	int	j;

	printf(" ------ print data ------ \n");
	printf("F = %ld\n", data->map.floor_hex);
	printf("C = %ld\n", data->map.ceiling_hex);
	printf("width = %d\n", data->map.width);
	printf("height = %d\n", data->map.height);
	printf("offset = %d\n", data->map.offset);
	i = -1;
	while (++i < data->map.height)
	{
		j = -1;
		while (++j < data->map.width + data->map.offset)
		{
			printf("%d", data->map.map[i][j]);
		}
		printf("\n");
	}
	printf(" ------------ \n");
	return (0);
}

/**
 * @brief initialize the data structure
 * @param data
 * @return
 *
*/
bool	ft_init(t_data *data)
{
	data->map.map_in_string = NULL;
	data->map.char_map = NULL;
	data->map.map = NULL;
	data->map.floor_hex = -1;
	data->map.ceiling_hex = -1;
	data->map.index = 'a';
	data->map.start_row = 0;
	data->map.start_col = 0;
	data->map.str_index = 0;
	data->map.offset = 0;
	data->fd = -1;
	while (++data->fd < 5)
	{
		data->texture_buffer[data->fd] = NULL;
		data->map.path_texture[data->fd] = NULL;
	}
	data->fd = 0;
	data->current_frame_time = 0.0;
	data->previous_frame_time = 0.0;
	data->mlx_ptr = mlx_init();
	if (!data->mlx_ptr)
		return (ft_err(EX11), false);
	data->current_frame_time = 0.0;
	data->previous_frame_time = 0.0;
	return (true);
}

int	main(int argc, char *argv[])
{
	t_data	data;

	(void)argv;
	if (argc != 2)
		return (ft_err(EIO), 1);
	if (!ft_init(&data))
		return (1);
	if (!ft_fill_and_parse_data(argv, &data))
		return (ft_free_data(&data), 1);
	ft_init_player(&data.player, &data);
	ft_init_window(&data);
	ft_free_data(&data);
	return (0);
}
