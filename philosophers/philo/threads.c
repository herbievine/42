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
#include "exit.h"
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>

static void	*ft_redirect_philo(void *arg);
static bool	ft_init_mutexes(t_data *data, t_philo *philos);
static void	ft_destroy_threads(t_data *data, t_philo *philos);

/**
 * @brief The ft_spawn_threads function creates the threads and initializes
 * the mutexes. It also sets the start time and the last meal time for each
 * philo. When the threads are created, it sets the is_ready flag to true, 
 * which allows the threads to start.
 * 
 * @param data 
 * @param philos 
 * @return bool 
 */
bool	ft_spawn_threads(t_data *data, t_philo *philos)
{
	int	i;

	if (!ft_init_mutexes(data, philos))
		return (false);
	pthread_mutex_lock(&data->data_mutex);
	data->start_time = ft_get_unix_time();
	pthread_mutex_unlock(&data->data_mutex);
	i = -1;
	while (++i < data->philo_count)
	{
		if (pthread_create(&philos[i].thread, NULL,
				&ft_redirect_philo, &philos[i]))
			return (false);
	}
	ft_wait_for_exit(data, philos);
	ft_destroy_threads(data, philos);
	return (true);
}

/**
 * @brief The ft_redirect_philo function is the function that is called by the
 * threads. It calls the ft_single_philo function if there is only one
 * philosopher, otherwise it calls the ft_multiple_philos function.
 * 
 * @param arg 
 * @return void* 
 */
static void	*ft_redirect_philo(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->data->max_eat == 0 || philo->data->time_die_in_ms == 0)
		return (NULL);
	pthread_mutex_lock(&philo->data->meal_mutex);
	philo->last_meal_time = ft_get_unix_time();
	pthread_mutex_unlock(&philo->data->meal_mutex);
	if (philo->data->philo_count == 1)
		ft_single_philo(philo);
	else
		ft_multiple_philos(philo);
	return (NULL);
}

/**
 * @brief The ft_init_mutexes function initializes the mutexes for the forks,
 * the data, the meal and the print. It returns false if any of the mutexes
 * fail to initialize.
 * 
 * @param data 
 * @param philos 
 * @return bool 
 */
static bool	ft_init_mutexes(t_data *data, t_philo *philos)
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

/**
 * @brief The ft_destroy_threads function destroys the threads and the mutexes.
 * 
 * @param data 
 * @param philos 
 */
static void	ft_destroy_threads(t_data *data, t_philo *philos)
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
}
