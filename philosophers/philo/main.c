/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 16:00:58 by herbie            #+#    #+#             */
/*   Updated: 2023/05/21 13:54:33 by herbie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"
#include "parse.h"
#include "time.h"
#include "error.h"
#include <stdio.h>

void	ft_init_data(t_data *data)
{
	data->philo_count = 0;
	data->time_die_in_ms = 0;
	data->time_eat_in_ms = 0;
	data->time_sleep_in_ms = 0;
	data->max_eat = -1;
	data->start_time_in_ms = 0;
}

int	main(int argc, char *argv[])
{
	t_data	data;

	ft_init_data(&data);
	if (!ft_parse_args(argc, argv, &data))
		return (ft_err(EARGS));
	data.start_time_in_ms = ft_get_time_in_ms();
	printf("philo_count: %d\n", data.philo_count);
	printf("time_die_in_ms: %d\n", data.time_die_in_ms);
	printf("time_eat_in_ms: %d\n", data.time_eat_in_ms);
	printf("time_sleep_in_ms: %d\n", data.time_sleep_in_ms);
	printf("max_eat: %d\n", data.max_eat);
	printf("start_time_in_ms: %d\n", data.start_time_in_ms);
	return (0);
}
