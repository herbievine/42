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
#include "threads.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

void	ft_init_forks(t_fork *forks, t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->philo_count)
		forks[i].is_taken = false;
}

void	ft_init_philos(t_philo *philos, t_data *data, t_fork *forks)
{
	int	i;

	i = -1;
	while (++i < data->philo_count)
	{
		philos[i].id = i + 1;
		philos[i].is_eating = false;
		philos[i].eat_count = 0;
		philos[i].data = data;
		philos[i].left_fork = &forks[i];
		philos[i].right_fork = &forks[(i + 1) % data->philo_count];
	}
}

void	ft_init_data(t_data *data)
{
	data->philo_count = 0;
	data->time_die_in_ms = 0;
	data->time_eat_in_ms = 0;
	data->time_sleep_in_ms = 0;
	data->max_eat = -1;
	data->start_time.tv_sec = 0;
	data->start_time.tv_usec = 0;
	data->is_dead = false;
}

int	main(int argc, char *argv[])
{
	t_data	data;
	t_philo	*philos;
	t_fork	*forks;

	ft_init_data(&data);
	if (!ft_parse_args(argc, argv, &data))
		return (ft_err(EARGS));
	forks = malloc(sizeof(t_fork) * data.philo_count);
	if (!forks)
		return (ft_err(EUNKN), 1);
	ft_init_forks(forks, &data);
	philos = malloc(sizeof(t_philo) * data.philo_count);
	if (!philos)
		return (ft_err(EUNKN), 1);
	ft_init_philos(philos, &data, forks);
	data.start_time = ft_get_time_in_ms();
	if (!ft_spawn_threads(&data, philos))
		return (ft_err(EUNKN));
	return (0);
}
