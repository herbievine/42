/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvine <hvine@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 13:55:35 by herbie            #+#    #+#             */
/*   Updated: 2023/06/20 06:49:59 by hvine            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "threads.h"
#include "structs.h"
#include "actions.h"
#include "time.h"
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

static void	ft_wait_for_exit(t_data *data, t_philo *philos)
{
	int	i;

	while (data->max_eat != 0 || !data->is_dead)
	{
		i = -1;
		while (++i < data->philo_count)
		{
			if (ft_get_time_diff_in_ms(philos[i].last_meal_time)
				> philos[i].data->time_die_in_ms)
			{
				printf("[%dms] %d died\n",
					ft_get_time_diff_in_ms(philos[i].data->start_time),
					philos[i].id);
				pthread_mutex_lock(&philos[i].data->data_mutex);
				data->is_dead = true;
				pthread_mutex_unlock(&philos[i].data->data_mutex);
				return ;
			}
		}
	}
}

void	*ft_philo_routine(void *arg)
{
	(void)arg;
	// t_philo	*philo;

	// philo = (t_philo *)arg;
	// while (!philo->data->is_dead)
	// {
	// 	ft_eat(philo);
	// 	ft_sleep_and_think(philo);
	// }
	return (NULL);
}

static t_bool	ft_destroy_threads(t_data *data, t_philo *philos)
{
	t_data	*data_to_free;
	int		i;

	data_to_free = ft_read_data_from_mutex(data);
	i = -1;
	while (++i < data_to_free->philo_count)
	{
		if (pthread_join(philos[i].thread, NULL)
			|| pthread_mutex_destroy(&(philos[i].right_fork->mutex)))
			return (false);
	}
	pthread_mutex_destroy(&data_to_free->print_mutex);
	pthread_mutex_destroy(&data_to_free->data_mutex);
	free(data_to_free);
	free(philos);
	return (true);
}

t_bool	ft_spawn_threads(t_data *data, t_philo *philos)
{
	int	i;

	i = -1;
	pthread_mutex_init(&data->print_mutex, NULL);
	pthread_mutex_init(&data->data_mutex, NULL);
	while (++i < data->philo_count)
	{
		pthread_mutex_init(&(philos[i].left_fork->mutex), NULL);
		pthread_mutex_init(&(philos[i].right_fork->mutex), NULL);
		philos[i].last_meal_time = ft_get_time_in_ms();
		if (pthread_create(&(philos[i].thread), NULL,
				&ft_philo_routine, &(philos[i])))
			return (false);
	}
	ft_wait_for_exit(data, philos);
	return (ft_destroy_threads(data, philos));
}
