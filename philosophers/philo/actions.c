/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 15:14:00 by herbie            #+#    #+#             */
/*   Updated: 2023/10/10 13:45:31 by codespace        ###   ########.fr       */
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
 * @brief The ft_single_philo function is used when there is only one
 * philosopher. It is used to print the first message.
 *
 * @param arg
 * @return void*
 */
void	*ft_single_philo(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	pthread_mutex_lock(&philo->data->print_mutex);
	printf("0 %d has taken a fork\n", philo->id);
	pthread_mutex_unlock(&philo->data->print_mutex);
	return (NULL);
}

/**
 * @brief The ft_multiple_philos function waits for the start of the game,
 * then the odd philosophers wait for the even ones to eat, and then they
 * start their cycle.
 *
 * @param arg
 * @return void*
 */
void	*ft_multiple_philos(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2)
		ft_usleep(philo->data->time_eat_in_ms, philo->data);
	while (pthread_mutex_lock(&philo->data->meal_mutex) == 0
		&& !philo->data->is_game_over)
	{
		pthread_mutex_unlock(&philo->data->meal_mutex);
		ft_eat(philo);
		ft_sleep_and_think(philo);
	}
	pthread_mutex_unlock(&philo->data->meal_mutex);
	return (NULL);
}

/**
 * @brief The ft_print function prints the message.
 *
 * @param philo
 * @param msg
 */
void	ft_print(t_philo *philo, char *msg)
{
	pthread_mutex_lock(&philo->data->meal_mutex);
	if (!philo->data->is_game_over)
	{
		pthread_mutex_lock(&philo->data->print_mutex);
		printf("%d %d %s\n",
			ft_get_time_diff(philo->data->start_time),
			philo->id, msg);
		pthread_mutex_unlock(&philo->data->print_mutex);
	}
	pthread_mutex_unlock(&philo->data->meal_mutex);
}

/**
 * @brief The ft_eat function locks the forks, eats and unlocks the forks.
 *
 * @param philo
 */
void	ft_eat(t_philo *philo)
{
	int	eat_time;

	pthread_mutex_lock(&philo->data->data_mutex);
	eat_time = philo->data->time_eat_in_ms;
	pthread_mutex_unlock(&philo->data->data_mutex);
	if (philo->id % 2)
		pthread_mutex_lock(philo->right_fork);
	else
		pthread_mutex_lock(philo->left_fork);
	ft_print(philo, "has taken a fork");
	if (philo->id % 2)
		pthread_mutex_lock(philo->left_fork);
	else
		pthread_mutex_lock(philo->right_fork);
	ft_print(philo, "has taken a fork");
	ft_print(philo, "is eating");
	pthread_mutex_lock(&philo->data->meal_mutex);
	philo->last_meal_time = ft_get_unix_time();
	philo->eat_count++;
	pthread_mutex_unlock(&philo->data->meal_mutex);
	ft_usleep(eat_time, philo->data);
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
	ft_print(philo, "is sleeping");
	ft_usleep(sleep_time, philo->data);
	ft_print(philo, "is thinking");
	if (philo->data->time_eat_in_ms > philo->data->time_sleep_in_ms)
		ft_usleep(philo->data->time_eat_in_ms - philo->data->time_sleep_in_ms,
			philo->data);
	ft_usleep(5, philo->data);
}
