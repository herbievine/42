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
 * @return int 
 */
int	ft_get_time_in_ms(void)
{
	t_timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		return (0);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

/**
 * @brief The ft_get_time_diff_in_ms function returns the difference between
 * the current time and the time passed in milliseconds.
 * 
 * @param time_in_ms 
 * @return int 
 */
int	ft_get_time_diff_in_ms(int time_in_ms)
{
	return (ft_get_time_in_ms() - time_in_ms);
}
