/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 15:14:00 by herbie            #+#    #+#             */
/*   Updated: 2023/06/24 15:52:10 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "actions.h"
#include "structs.h"
#include "time.h"
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/time.h>

/**
 * @brief The ft_print function prints the message with the current time.
 *
 * @param philo
 * @param msg
 */
static void	ft_print(t_philo *philo, char *msg, int arg_ms)
{
	int	diff;

	pthread_mutex_lock(&philo->data->meal_mutex);
	if (!philo->data->is_game_over)
	{
		pthread_mutex_lock(&philo->data->print_mutex);
		diff = ft_get_time_diff_in_ms(philo->data->start_time);
		printf("[%dms] %d %s\n", diff - diff % arg_ms, philo->id, msg);
		pthread_mutex_unlock(&philo->data->print_mutex);
	}
	pthread_mutex_unlock(&philo->data->meal_mutex);
}

/**
 * @brief The ft_eat function takes two forks, eats and then releases them.
 *
 * @param philo
 */
void	ft_eat(t_philo *philo)
{
	int	eat_time;

	pthread_mutex_lock(&philo->data->data_mutex);
	eat_time = philo->data->time_eat_in_ms;
	pthread_mutex_unlock(&philo->data->data_mutex);
	pthread_mutex_lock(philo->left_fork);
	ft_print(philo, "has taken a fork", eat_time);
	pthread_mutex_lock(philo->right_fork);
	ft_print(philo, "has taken a fork", eat_time);
	ft_print(philo, "is eating", eat_time);
	pthread_mutex_lock(&philo->data->meal_mutex);
	philo->last_meal_time = ft_get_time_in_ms();
	philo->eat_count++;
	pthread_mutex_unlock(&philo->data->meal_mutex);
	ft_usleep(eat_time);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

/**
 * @brief The ft_sleep_and_think function sleeps and thinks.
 *
 * @param philo
 */
void	ft_sleep_and_think(t_philo *philo)
{
	int	sleep_time;

	pthread_mutex_lock(&philo->data->data_mutex);
	sleep_time = philo->data->time_sleep_in_ms;
	pthread_mutex_unlock(&philo->data->data_mutex);
	ft_print(philo, "is sleeping", sleep_time);
	ft_usleep(sleep_time);
	ft_print(philo, "is thinking", sleep_time);
}
