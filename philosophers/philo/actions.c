/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 15:14:00 by herbie            #+#    #+#             */
/*   Updated: 2023/06/21 07:53:49 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "actions.h"
#include "structs.h"
#include "time.h"
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

/**
 * @brief The ft_internal_usleep function sleeps for the specified time in
 * milliseconds. If the philosopher is dead, the function returns.
 *
 * @param data
 * @param time
 */
static void ft_internal_usleep(t_data *data, unsigned long time)
{
	unsigned long start_time;

	start_time = ft_get_time_in_ms();
	while ((unsigned long)ft_get_time_diff_in_ms(start_time) < time)
	{
		if (data->is_game_over)
			break;
		usleep(100);
	}
}

/**
 * @brief The ft_print function prints the message with the current time.
 *
 * @param philo
 * @param msg
 */
static void ft_print(t_philo *philo, char *msg)
{
	pthread_mutex_lock(&philo->data->mutex);
	if (!philo->data->is_game_over)
		printf("[%dms] %d %s\n", ft_get_time_diff_in_ms(philo->data->start_time),
					 philo->id, msg);
	pthread_mutex_unlock(&philo->data->mutex);
}

/**
 * @brief The ft_eat function takes two forks, eats and then releases them.
 *
 * @param philo
 */
void ft_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->left_fork->mutex);
	ft_print(philo, "has taken a fork");
	pthread_mutex_lock(&philo->right_fork->mutex);
	ft_print(philo, "has taken a fork");
	ft_print(philo, "is eating");
	philo->last_meal_time = ft_get_time_in_ms();
	philo->eat_count++;
	pthread_mutex_lock(&philo->data->mutex);
	ft_internal_usleep(philo->data, philo->data->time_eat_in_ms);
	pthread_mutex_unlock(&philo->data->mutex);
	pthread_mutex_unlock(&philo->left_fork->mutex);
	pthread_mutex_unlock(&philo->right_fork->mutex);
}

/**
 * @brief The ft_sleep_and_think function sleeps and thinks.
 *
 * @param philo
 */
void ft_sleep_and_think(t_philo *philo)
{
	ft_print(philo, "is sleeping");
	pthread_mutex_lock(&philo->data->mutex);
	ft_internal_usleep(philo->data, philo->data->time_sleep_in_ms);
	pthread_mutex_unlock(&philo->data->mutex);
	ft_print(philo, "is thinking");
}
