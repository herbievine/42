/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcros <jcros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 16:00:58 by herbie            #+#    #+#             */
/*   Updated: 2024/03/26 15:42:30 by jcros            ###   ########.fr       */
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
#include <stdio.h>
#include <stdlib.h>

// t_data	ft_init(void)
// {
// 	t_data	data;

// 	return (data);
// }

void ft_modify_map(t_data *data)
{
	int i;
	int j;

	i = 0;
	while (i < data->map.height)
	{
		j = 0;
		while (j < data->map.width + data->map.offset)
		{
			if (i == 0)
			{
				data->map.map[i][j] = 2;
			}
			if (i == data->map.height - 1)
			{
				data->map.map[i][j] = 3;
			}
			if (j == 0)
			{
				data->map.map[i][j] = 4;
			}
			j++;
		}
		i++;
	}
}

void	ft_print_map(t_data *data)
{
	int i;
	int j;

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
		ft_err(EIO);
	ft_init(&data);
	if (!ft_fill_and_parse_data(argv, &data))
		return (ft_free_data(&data), 1);
	ft_init_player(&data.player, &data);
	// ft_modify_map(&data);
	// ft_print_map(&data);
	ft_print_data(&data);
	ft_init_window(&data);
	ft_free_data(&data);
	return (0);
}
