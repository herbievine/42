/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 13:55:35 by herbie            #+#    #+#             */
/*   Updated: 2023/06/23 08:31:58 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "threads.h"
#include "structs.h"
#include "actions.h"
#include "time.h"
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

// static void ft_wait_for_exit(t_data *data, t_philo *philos)
// {
// 	int i;

// 	while (true)
// 	{
// 		pthread_mutex_lock(&data->mutex);
// 		while (!data->is_game_over)
// 		{
// 			i = -1;
// 			while (++i < data->philo_count)
// 			{
// 				if (ft_get_time_diff_in_ms(philos[i].last_meal_time)
// 					> data->time_die_in_ms)
// 				{
// 					printf("[%dms] %d died\n",
// 						ft_get_time_diff_in_ms(data->start_time),
// 						philos[i].id);
// 					pthread_mutex_lock(&data->mutex);
// 					data->is_game_over = true;
// 					return ;
// 				}
// 			}
// 		}
// 	}

// 	// while (data->max_eat != 0 || !data->is_game_over)
// 	// {
// 	// 	i = -1;
// 	// 	while (++i < data->philo_count)
// 	// 	{
// 	// 		if (ft_get_time_diff_in_ms(philos[i].last_meal_time) > philos[i].data->time_die_in_ms)
// 	// 		{
// 	// 			printf("[%dms] %d died\n",
// 	// 						 ft_get_time_diff_in_ms(philos[i].data->start_time),
// 	// 						 philos[i].id);
// 	// 			pthread_mutex_lock(&philos[i].data->mutex);
// 	// 			data->is_game_over = true;
// 	// 			return;
// 	// 		}
// 	// 	}
// 	// }
// }

static void *ft_philo_routine(void *arg)
{
	t_philo *philo;

	philo = (t_philo *)arg;
	while (true)
	{
		pthread_mutex_lock(&philo->data->mutex);
		if (philo->data->is_ready)
		{
			pthread_mutex_unlock(&philo->data->mutex);
			break;
		}
		pthread_mutex_unlock(&philo->data->mutex);
	}
	if (philo->id & 1)
	{
		pthread_mutex_lock(&philo->data->mutex);
		ft_usleep(philo->data->time_eat_in_ms * 0.9 + 1);
		pthread_mutex_unlock(&philo->data->mutex);
	}
	// while (true)
	// {
	// 	pthread_mutex_lock(&philo->data->mutex);
	// 	if (!philo->data->is_game_over)
	// 	{
	// 		// ft_eat(philo);
	// 		// ft_sleep_and_think(philo);
	// 	}
	// 	else
	// 	{
	// 		pthread_mutex_unlock(&philo->data->mutex);
	// 		break;
	// 	}
	// 	pthread_mutex_unlock(&philo->data->mutex);
	// }
	// printf("philo %d is ready\n", philo->id);
	return (NULL);
}

static t_bool ft_destroy_threads(t_data *data, t_philo *philos)
{
	int i;

	i = -1;
	while (++i < data->philo_count)
	{
		if (pthread_join(philos[i].thread, NULL) || pthread_mutex_destroy(philos[i].right_fork))
			return (false);
	}
	pthread_mutex_destroy(&data->mutex);
	free(philos);
	return (true);
}

t_bool ft_init_mutexes(t_data *data, t_philo *philos)
{
	int i;

	i = -1;
	while (++i < data->philo_count)
	{
		if (pthread_mutex_init(philos[i].left_fork, NULL) != 0 || pthread_mutex_init(philos[i].right_fork, NULL) != 0)
			return (false);
	}
	if (pthread_mutex_init(&data->mutex, NULL) != 0)
		return (false);
	return (true);
}

t_bool ft_spawn_threads(t_data *data, t_philo *philos)
{
	int i;

	if (!ft_init_mutexes(data, philos))
		return (false);
	i = -1;
	pthread_mutex_init(&data->mutex, NULL);
	while (++i < data->philo_count)
	{
		if (pthread_create(&philos[i].thread, NULL,
											 &ft_philo_routine, &philos[i]))
			return (false);
	}
	pthread_mutex_lock(&data->mutex);
	// data->start_time = ft_get_time_in_ms();
	// i = -1;
	// while (++i < data->philo_count)
	// 	philos[i].last_meal_time = data->start_time;
	data->is_ready = true;
	pthread_mutex_unlock(&data->mutex);
	// ft_wait_for_exit(data, philos);
	return (ft_destroy_threads(data, philos));
}
