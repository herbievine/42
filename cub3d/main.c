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
#include "structs.h"
#include "parse.h"
#include "error.h"
#include "window.h"
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

	if (argc != 2)
		ft_err(EIO);
	// data = ft_init();
	ft_parse_map_or_throw(&data.map, argv[1]);
	ft_init_window(&data);
	return (0);
}
