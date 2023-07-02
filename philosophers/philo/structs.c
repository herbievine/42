/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 10:56:37 by herbie            #+#    #+#             */
/*   Updated: 2023/06/23 08:28:17 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"
#include <stdlib.h>

/**
 * @brief The ft_init_philos function initializes the philos array with the
 * correct values.
 * 
 * @param philos 
 * @param data 
 * @param forks 
 */
void	ft_init_philos(t_philo *philos, t_data *data, pthread_mutex_t *forks)
{
	int	i;

	i = -1;
	while (++i < data->philo_count)
	{
		philos[i].id = i + 1;
		philos[i].eat_count = 0;
		philos[i].data = data;
		philos[i].left_fork = &forks[i];
		philos[i].right_fork = &forks[(i + 1) % data->philo_count];
	}
}

/**
 * @brief The ft_init_data function initializes the data struct with the
 * correct values.
 * 
 * @param data 
 */
void	ft_init_data(t_data *data)
{
	data->philo_count = 0;
	data->time_die_in_ms = 0;
	data->time_eat_in_ms = 0;
	data->time_sleep_in_ms = 0;
	data->max_eat = -1;
	data->start_time = 0;
	data->is_ready = false;
	data->is_game_over = false;
}
