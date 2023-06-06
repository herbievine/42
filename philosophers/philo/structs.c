/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 10:56:37 by herbie            #+#    #+#             */
/*   Updated: 2023/05/22 10:56:37 by herbie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"
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
	data->start_time = 0;
	data->is_dead = false;
}

t_data	*ft_read_data_from_mutex(t_data *data)
{
	t_data	*result;

	pthread_mutex_lock(&data->data_mutex);
	result = malloc(sizeof(t_data));
	if (!result)
		return (NULL);
	result->philo_count = data->philo_count;
	result->time_die_in_ms = data->time_die_in_ms;
	result->time_eat_in_ms = data->time_eat_in_ms;
	result->time_sleep_in_ms = data->time_sleep_in_ms;
	result->max_eat = data->max_eat;
	result->start_time = data->start_time;
	result->is_dead = data->is_dead;
	pthread_mutex_unlock(&data->data_mutex);
	return (result);
}
