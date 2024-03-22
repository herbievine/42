/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juliencros <juliencros@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 16:00:58 by herbie            #+#    #+#             */
/*   Updated: 2024/03/22 09:45:02 by juliencros       ###   ########.fr       */
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
	// ft_print_data(&data);
	ft_init_window(&data);
	ft_free_data(&data);
	return (0);
}
