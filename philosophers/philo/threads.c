/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 13:55:35 by herbie            #+#    #+#             */
/*   Updated: 2023/05/21 15:33:49 by herbie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "threads.h"
#include "structs.h"
#include "actions.h"
#include "time.h"
#include <pthread.h>
#include <stdio.h>

t_bool	hasDied(t_philo *philo)
{
	if (ft_get_time_diff_in_ms(philo->last_meal_time)
		> philo->data->time_die_in_ms)
		return (true);
	return (false);
}

void	*ft_philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (42 && philo->data->is_dead == false)
	{
		ft_take_forks(philo);
		ft_eat(philo);
		ft_sleep(philo);
		ft_think(philo);
		if (hasDied(philo))
		{
			printf("[%dms] %d died\n", ft_get_time_diff_in_ms(philo->data->start_time), philo->id);
			return (NULL);
		}
	}
	return (NULL);
}

t_bool	ft_spawn_threads(t_data *data, t_philo *philos)
{
	int	i;

	i = -1;
	while (++i < data->philo_count)
	{
		pthread_mutex_init(&(philos[i].left_fork->mutex), NULL);
		pthread_mutex_init(&(philos[i].right_fork->mutex), NULL);
		if (pthread_create(&(philos[i].thread), NULL,
				&ft_philo_routine, &(philos[i])))
			return (false);
	}
	i = -1;
	while (++i < data->philo_count)
	{
		if (pthread_join(philos[i].thread, NULL))
			return (false);
		pthread_mutex_destroy(&(philos[i].left_fork->mutex));
		pthread_mutex_destroy(&(philos[i].right_fork->mutex));
	}
	return (true);
}
