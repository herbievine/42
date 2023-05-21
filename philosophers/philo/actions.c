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
 * @brief The ft_take_forks function locks the mutexes of the left and right
 * forks.
 * 
 * @param philo 
 */
void	ft_take_forks(t_philo *philo)
{
	pthread_mutex_lock(&(philo->left_fork->mutex));
	printf("[%dms] %d has taken a fork\n",
		ft_get_time_diff_in_ms(philo->data->start_time), philo->id);
	pthread_mutex_lock(&(philo->right_fork->mutex));
	printf("[%dms] %d has taken a fork\n",
		ft_get_time_diff_in_ms(philo->data->start_time), philo->id);
}

/**
 * @brief The ft_eat function prints that the philosopher is eating, updates
 * the last meal time and sleeps for the specified time in milliseconds. It
 * then unlocks the mutexes of the left and right forks.
 * 
 * @param philo 
 */
void	ft_eat(t_philo *philo)
{
	printf("[%dms] %d is eating\n",
		ft_get_time_diff_in_ms(philo->data->start_time), philo->id);
	philo->last_meal_time = ft_get_time_in_ms();
	ft_internal_usleep(philo, philo->data->time_eat_in_ms);
	pthread_mutex_unlock(&(philo->left_fork->mutex));
	pthread_mutex_unlock(&(philo->right_fork->mutex));
}

/**
 * @brief The ft_sleep function prints that the philosopher is sleeping and
 * sleeps for the specified time in milliseconds.
 * 
 * @param philo 
 */
void	ft_sleep(t_philo *philo)
{
	printf("[%dms] %d is sleeping\n",
		ft_get_time_diff_in_ms(philo->data->start_time), philo->id);
	ft_internal_usleep(philo, philo->data->time_sleep_in_ms);
}

/**
 * @brief The ft_think function prints that the philosopher is thinking.
 * 
 * @param philo 
 */
void	ft_think(t_philo *philo)
{
	printf("[%dms] %d is thinking\n",
		ft_get_time_diff_in_ms(philo->data->start_time), philo->id);
}
