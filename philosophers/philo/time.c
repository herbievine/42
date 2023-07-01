/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 14:19:23 by herbie            #+#    #+#             */
/*   Updated: 2023/05/21 14:19:23 by herbie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "time.h"
#include "structs.h"
#include <sys/time.h>
#include <stdlib.h>
#include <unistd.h>

/**
 * @brief The ft_get_time_in_ms function returns the current time in
 * milliseconds.
 * 
 * @return unsigned long 
 */
unsigned long	ft_get_time_in_ms(void)
{
	t_timeval	time;

	gettimeofday(&time, NULL);
	return ((unsigned long)(time.tv_sec * 1000 + time.tv_usec / 1000));
}

/**
 * @brief The ft_get_time_diff_in_ms function returns the difference between
 * the current time and the time passed in milliseconds.
 * 
 * @param time
 * @return int 
 */
int	ft_get_time_diff_in_ms(unsigned long time)
{
	unsigned long	current_time;

	current_time = ft_get_time_in_ms();
	return ((int)(current_time - time));
}

/**
 * @brief The ft_usleep function sleeps for the specified time in
 * milliseconds.
 *
 * @param time
 */
void	ft_usleep(unsigned long time)
{
	unsigned long	start_time;

	start_time = ft_get_time_in_ms();
	while ((unsigned long)ft_get_time_diff_in_ms(start_time) < time)
		usleep(100);
}
