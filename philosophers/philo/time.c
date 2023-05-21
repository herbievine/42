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

/**
 * @brief The ft_get_time_in_ms function returns the current time in
 * milliseconds.
 * 
 * @return t_timeval 
 */
t_timeval	ft_get_time_in_ms(void)
{
	t_timeval	time;

	gettimeofday(&time, NULL);
	return (time);
}

/**
 * @brief The ft_get_time_diff_in_ms function returns the difference between
 * the current time and the time passed in milliseconds.
 * 
 * @param time
 * @return int 
 */
int	ft_get_time_diff_in_ms(t_timeval time)
{
	t_timeval	current_time;

	current_time = ft_get_time_in_ms();
	current_time.tv_sec -= time.tv_sec;
	current_time.tv_usec -= time.tv_usec;
	return (current_time.tv_sec * 1000 + current_time.tv_usec / 1000);
}
