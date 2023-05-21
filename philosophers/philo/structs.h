/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 11:39:52 by herbie            #+#    #+#             */
/*   Updated: 2023/05/21 14:11:55 by herbie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include <sys/time.h>

typedef enum e_bool
{
	false,
	true
}	t_bool;

typedef struct timeval	t_timeval;

typedef struct s_data
{
	int	philo_count;
	int	time_die_in_ms;
	int	time_eat_in_ms;
	int	time_sleep_in_ms;
	int	max_eat;
	int	start_time_in_ms;
}	t_data;

#endif /* STRUCTS_H */