/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 13:55:35 by herbie            #+#    #+#             */
/*   Updated: 2023/06/30 12:31:58 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "threads.h"
#include "structs.h"
#include "actions.h"
#include "time.h"
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

static void	ft_wait_for_exit(t_data *data, t_philo *philos)
{
	int	i;
	int	eat_count;

	while (true)
	{
		i = -1;
		while (++i < data->philo_count)
		{
			pthread_mutex_lock(&data->meal_mutex);
			if (ft_get_time_diff_in_ms(philos[i].last_meal_time)
				> data->time_die_in_ms)
			{
				pthread_mutex_lock(&data->print_mutex);
				printf("[%dms] %d died\n",
					ft_get_time_diff_in_ms(data->start_time),
					philos[i].id);
				data->is_game_over = true;
				pthread_mutex_unlock(&data->print_mutex);
				pthread_mutex_unlock(&data->meal_mutex);
				return ;
			}
			pthread_mutex_unlock(&data->meal_mutex);
		}
	}
}

static void	*ft_philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (pthread_mutex_lock(&philo->data->data_mutex) == 0
		&& !philo->data->is_ready)
		pthread_mutex_unlock(&philo->data->data_mutex);
	pthread_mutex_unlock(&philo->data->data_mutex);
	if (philo->id & 1)
	{
		pthread_mutex_lock(&philo->data->data_mutex);
		usleep(philo->data->time_eat_in_ms * 0.9 + 1);
		pthread_mutex_unlock(&philo->data->data_mutex);
	}
	while (pthread_mutex_lock(&philo->data->meal_mutex) == 0
		&& !philo->data->is_game_over)
	{
		pthread_mutex_unlock(&philo->data->meal_mutex);
		ft_eat(philo);
		ft_sleep_and_think(philo);
	}
	pthread_mutex_unlock(&philo->data->meal_mutex);
	return (NULL);
}

static t_bool	ft_destroy_threads(t_data *data, t_philo *philos)
{
	int	i;

	i = -1;
	while (++i < data->philo_count)
		pthread_join(philos[i].thread, NULL);
	i = -1;
	while (++i < data->philo_count)
		pthread_mutex_destroy(philos[i].left_fork);
	pthread_mutex_destroy(&data->data_mutex);
	pthread_mutex_destroy(&data->meal_mutex);
	pthread_mutex_destroy(&data->print_mutex);
	return (true);
}

static t_bool	ft_init_mutexes(t_data *data, t_philo *philos)
{
	int	i;

	i = -1;
	while (++i < data->philo_count)
	{
		if (pthread_mutex_init(philos[i].left_fork, NULL) != 0)
			return (false);
	}
	if (pthread_mutex_init(&data->data_mutex, NULL) != 0)
		return (false);
	if (pthread_mutex_init(&data->meal_mutex, NULL) != 0)
		return (false);
	if (pthread_mutex_init(&data->print_mutex, NULL) != 0)
		return (false);
	return (true);
}

t_bool	ft_spawn_threads(t_data *data, t_philo *philos)
{
	int	i;

	if (!ft_init_mutexes(data, philos))
		return (false);
	i = -1;
	while (++i < data->philo_count)
	{
		if (pthread_create(&philos[i].thread, NULL,
				&ft_philo_routine, &philos[i]))
			return (false);
	}
	pthread_mutex_lock(&data->data_mutex);
	data->start_time = ft_get_time_in_ms();
	i = -1;
	while (++i < data->philo_count)
		philos[i].last_meal_time = data->start_time;
	data->is_ready = true;
	pthread_mutex_unlock(&data->data_mutex);
	ft_wait_for_exit(data, philos);
	return (ft_destroy_threads(data, philos));
}
