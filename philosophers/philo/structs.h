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
# include <pthread.h>

typedef enum e_bool
{
	false,
	true
}	t_bool;

typedef struct timeval	t_timeval;

typedef struct s_fork
{
	pthread_mutex_t	mutex;
	t_bool			is_taken;
}	t_fork;

typedef struct s_data
{
	int				philo_count;
	int				time_die_in_ms;
	int				time_eat_in_ms;
	int				time_sleep_in_ms;
	int				max_eat;
	unsigned long	start_time;
	t_bool			is_dead;
	pthread_mutex_t	print_mutex;
}	t_data;

typedef struct s_philo
{
	int				id;
	t_bool			is_eating;
	int				eat_count;
	t_data			*data;
	t_fork			*left_fork;
	t_fork			*right_fork;
	unsigned long	last_meal_time;
	pthread_t		thread;
}	t_philo;

#endif /* STRUCTS_H */