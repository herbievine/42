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

static void		*ft_redirect_philo(void *arg);
static t_bool	ft_init_mutexes(t_data *data, t_philo *philos);
static void		ft_destroy_threads(t_data *data, t_philo *philos);

t_bool	ft_spawn_threads(t_data *data, t_philo *philos)
{
	int	i;

	if (!ft_init_mutexes(data, philos))
		return (false);
	i = -1;
	while (++i < data->philo_count)
	{
		if (pthread_create(&philos[i].thread, NULL,
				&ft_redirect_philo, &philos[i]))
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
	ft_destroy_threads(data, philos);
	return (true);
}

static void	*ft_redirect_philo(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->data->philo_count == 1)
		ft_single_philo(philo);
	else
		ft_multiple_philos(philo);
	return (NULL);
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
