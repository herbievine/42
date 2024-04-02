/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcros <jcros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 16:00:58 by herbie            #+#    #+#             */
/*   Updated: 2024/04/02 15:22:51 by jcros            ###   ########.fr       */
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
	printf("NO = %p\n", data->textures[0].img);
	printf("SO = %p\n", data->textures[1].img);
	printf("WE = %p\n", data->textures[2].img);
	printf("EA = %p\n", data->textures[3].img);
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

void	ft_init(t_data *data)
{
	data->map.map_in_string = NULL;
	data->map.char_map = NULL;
	data->map.map = NULL;
	data->map.no_img = NULL;
	data->map.so_img = NULL;
	data->map.we_img = NULL;
	data->map.ea_img = NULL;
	data->map.floor_hex = -1;
	data->map.ceiling_hex = -1;
	data->map.width = 0;
	data->map.height = 0;
	data->map.index = 'a';
	data->map.start_row = 0;
	data->map.start_col = 0;
	data->map.str_index = 0;
	data->map.offset = 0;
	data->mlx_ptr = NULL;
	data->fd = 0;
	data->map.path_texture = ft_calloc(sizeof(char *), 4);
	if (data->map.path_texture == NULL)
		ft_err("Malloc failed");
	data->mlx_ptr = mlx_init();
	if (!data->mlx_ptr)
		return (ft_err(EX11));
}

void	ft_print_map(t_data *data)
{
	int	i;
	int	j;

	i = 0;
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
}

int	main(int argc, char *argv[])
{
	t_data	data;

	(void)argv;
	if (argc != 2)
		return (ft_err(EIO), 1);
	ft_init(&data);
	if (!ft_fill_and_parse_data(argv, &data))
		return (ft_free_data(&data), 1);
	ft_init_player(&data.player, &data);
	ft_print_data(&data);
	ft_init_window(&data);
	ft_free_data(&data);
	return (0);
}
