/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/01 18:31:57 by codespace         #+#    #+#             */
/*   Updated: 2023/10/15 17:03:31 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exit.h"
#include "time.h"
#include "structs.h"
#include <pthread.h>
#include <stdio.h>

static t_bool	ft_did_die(t_data *data, t_philo *philo);
static t_bool	ft_did_eat(t_data *data, t_philo *philos);

/**
 * @brief The ft_wait_for_exit function waits for a philosopher to die or for
 * all philosophers to eat the maximum number of times.
 *
 * @param data
 * @param philos
 */
void	ft_wait_for_exit(t_data *data, t_philo *philos)
{
	int	i;

	while (true)
	{
		ft_usleep(5, data);
		i = -1;
		while (++i < data->philo_count)
		{
			if (ft_did_die(data, &philos[i]))
				return ;
			if (ft_did_eat(data, philos))
				return ;
		}
	}
}

/**
 * @brief The ft_did_die function checks if a philosopher has died. If so, it
 * prints a message to the standard output and sets the is_game_over flag to
 * true.
 *
 * @param data
 * @param philo
 * @return t_bool
 */
static t_bool	ft_did_die(t_data *data, t_philo *philo)
{
	pthread_mutex_lock(&data->meal_mutex);
	if (ft_get_time_diff(philo->last_meal_time) > data->time_die_in_ms)
	{
		pthread_mutex_lock(&data->print_mutex);
		printf("%d %d died\n",
			ft_get_time_diff(data->start_time),
			philo->id);
		data->is_game_over = true;
		pthread_mutex_unlock(&data->print_mutex);
		pthread_mutex_unlock(&data->meal_mutex);
		return (true);
	}
	pthread_mutex_unlock(&data->meal_mutex);
	return (false);
}

/**
 * @brief The ft_did_eat function checks if all philosophers have eaten the
 * maximum number of times. If so, it prints a message to the standard output
 * and sets the is_game_over flag to true.
 *
 * @param data
 * @param philos
 * @return t_bool
 */
static t_bool	ft_did_eat(t_data *data, t_philo *philos)
{
	int	i;
	int	have_all_eaten;

	i = -1;
	have_all_eaten = 0;
	pthread_mutex_lock(&data->meal_mutex);
	while (++i < data->philo_count && data->max_eat != -1)
		if (philos[i].eat_count >= data->max_eat)
			have_all_eaten++;
	if (have_all_eaten == data->philo_count)
	{
		pthread_mutex_lock(&data->print_mutex);
		printf("%d all philosophers have eaten %d times\n",
			ft_get_time_diff(data->start_time),
			data->max_eat);
		data->is_game_over = true;
		pthread_mutex_unlock(&data->print_mutex);
		pthread_mutex_unlock(&data->meal_mutex);
		return (true);
	}
	pthread_mutex_unlock(&data->meal_mutex);
	return (false);
}
