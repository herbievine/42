/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 15:14:00 by herbie            #+#    #+#             */
/*   Updated: 2023/05/21 15:14:00 by herbie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "actions.h"
#include "structs.h"
#include "time.h"
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

void	ft_take_forks(t_philo *philo)
{
	pthread_mutex_lock(&(philo->left_fork->mutex));
	printf("[%dms] %d has taken a fork\n", ft_get_time_diff_in_ms(philo->data->start_time), philo->id);
	pthread_mutex_lock(&(philo->right_fork->mutex));
	printf("[%dms] %d has taken a fork\n", ft_get_time_diff_in_ms(philo->data->start_time), philo->id);
}

void	ft_eat(t_philo *philo)
{
	printf("[%dms] %d is eating\n", ft_get_time_diff_in_ms(philo->data->start_time), philo->id);
	usleep(philo->data->time_eat_in_ms * 1000);
	philo->last_meal_time = ft_get_time_in_ms();
	pthread_mutex_unlock(&(philo->left_fork->mutex));
	pthread_mutex_unlock(&(philo->right_fork->mutex));
}

void	ft_sleep(t_philo *philo)
{
	printf("[%dms] %d is sleeping\n", ft_get_time_diff_in_ms(philo->data->start_time), philo->id);
	usleep(philo->data->time_sleep_in_ms * 1000);
}

void	ft_think(t_philo *philo)
{
	printf("[%dms] %d is thinking\n", ft_get_time_diff_in_ms(philo->data->start_time), philo->id);
}
