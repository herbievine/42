/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 14:19:23 by herbie            #+#    #+#             */
/*   Updated: 2023/07/01 18:16:40 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "time.h"
#include "structs.h"
#include <sys/time.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>

/**
 * @brief The ft_get_unix_time function returns the current time in
 * milliseconds.
 * 
 * @return uint64_t 
 */
uint64_t	ft_get_unix_time(void)
{
	t_timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * (uint64_t)1000) + (time.tv_usec / 1000));
}

/**
 * @brief The ft_get_time_diff function returns the difference between
 * the current time and the time passed in milliseconds.
 * 
 * @param time
 * @return int 
 */
int	ft_get_time_diff(uint64_t time)
{
	uint64_t	current_time;

	current_time = ft_get_unix_time();
	return ((int)(current_time - time));
}

/**
 * @brief The ft_usleep function sleeps for the specified time in
 * milliseconds.
 *
 * @param time
 */
void	ft_usleep(uint64_t time, t_data *data)
{
	uint64_t	start_time;

	start_time = ft_get_unix_time();
	while ((uint64_t)ft_get_time_diff(start_time) < time)
	{
		pthread_mutex_lock(&data->meal_mutex);
		if (data->is_game_over)
			return (pthread_mutex_unlock(&data->meal_mutex), (void)0);
		pthread_mutex_unlock(&data->meal_mutex);
		usleep(100);
	}
}
