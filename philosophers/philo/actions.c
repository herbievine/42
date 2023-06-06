/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 15:14:00 by herbie            #+#    #+#             */
/*   Updated: 2023/05/21 21:04:59 by herbie           ###   ########.fr       */
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
 * @param philo 
 * @param time 
 */
static void	ft_internal_usleep(t_philo *philo, unsigned long time)
{
	unsigned long	start_time;

	start_time = ft_get_time_in_ms();
	while ((unsigned long)ft_get_time_diff_in_ms(start_time) < time)
	{
		if (philo->data->is_dead)
			break ;
		usleep(100);
	}
}

/**
 * @brief The ft_print function prints the message with the current time.
 * 
 * @param philo 
 * @param msg 
 */
static void	ft_print(t_philo *philo, char *msg)
{
	pthread_mutex_lock(&philo->data->print_mutex);
	pthread_mutex_lock(&philo->data->data_mutex);
	if (!philo->data->is_dead)
		printf("[%dms] %d %s\n", ft_get_time_diff_in_ms(philo->data->start_time),
			philo->id, msg);
	pthread_mutex_unlock(&philo->data->print_mutex);
	pthread_mutex_unlock(&philo->data->data_mutex);
}

/**
 * @brief The ft_eat function takes two forks, eats and then releases them.
 * 
 * @param philo 
 */
void	ft_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->left_fork->mutex);
	ft_print(philo, "has taken a fork");
	pthread_mutex_lock(&philo->right_fork->mutex);
	ft_print(philo, "has taken a fork");
	ft_print(philo, "is eating");
	philo->last_meal_time = ft_get_time_in_ms();
	pthread_mutex_lock(&philo->data->data_mutex);
	ft_internal_usleep(philo, philo->data->time_eat_in_ms);
	pthread_mutex_unlock(&philo->data->data_mutex);
	pthread_mutex_unlock(&philo->left_fork->mutex);
	pthread_mutex_unlock(&philo->right_fork->mutex);
}

/**
 * @brief The ft_sleep_and_think function sleeps and thinks.
 * 
 * @param philo 
 */
void	ft_sleep_and_think(t_philo *philo)
{
	ft_print(philo, "is sleeping");
	pthread_mutex_lock(&philo->data->data_mutex);
	ft_internal_usleep(philo, philo->data->time_sleep_in_ms);
	pthread_mutex_unlock(&philo->data->data_mutex);
	ft_print(philo, "is thinking");
}
