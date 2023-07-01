/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/01 18:31:57 by codespace         #+#    #+#             */
/*   Updated: 2023/07/01 18:31:57 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exit.h"
#include "time.h"
#include "structs.h"
#include <pthread.h>
#include <stdio.h>

static t_bool	ft_did_die(t_data *data, t_philo *philo);
static t_bool	ft_did_eat(t_data *data, t_philo *philos);

void	ft_wait_for_exit(t_data *data, t_philo *philos)
{
	int	i;

	while (true)
	{
		i = -1;
		while (++i < data->philo_count)
		{
			if (ft_did_die(data, &philos[i]))
				return ;
			if (ft_did_eat(data, &philos[i]))
				return ;
		}
	}
}

static t_bool	ft_did_die(t_data *data, t_philo *philo)
{
	pthread_mutex_lock(&data->meal_mutex);
	if (ft_get_time_diff(philo->last_meal_time)
		> data->time_die_in_ms)
	{
		pthread_mutex_lock(&data->print_mutex);
		printf("[%dms] %d died\n",
			ft_get_rounded_time_diff(data->start_time, data->time_die_in_ms),
			philo->id);
		data->is_game_over = true;
		pthread_mutex_unlock(&data->print_mutex);
		pthread_mutex_unlock(&data->meal_mutex);
		return (true);
	}
	pthread_mutex_unlock(&data->meal_mutex);
	return (false);
}

static t_bool	ft_did_eat(t_data *data, t_philo *philos)
{
	int	i;
	int	have_all_eaten;

	i = -1;
	have_all_eaten = 0;
	pthread_mutex_lock(&data->meal_mutex);
	while (++i < data->philo_count && data->max_eat != -1)
	{
		if (philos[i].eat_count >= data->max_eat)
			have_all_eaten++;
	}
	if (have_all_eaten == data->philo_count)
	{
		pthread_mutex_lock(&data->print_mutex);
		printf("[%dms] all philosophers have eaten %d times\n",
			ft_get_rounded_time_diff(data->start_time, data->time_eat_in_ms),
			data->max_eat);
		data->is_game_over = true;
		pthread_mutex_unlock(&data->print_mutex);
		pthread_mutex_unlock(&data->meal_mutex);
		return (true);
	}
	pthread_mutex_unlock(&data->meal_mutex);
	return (false);
}
