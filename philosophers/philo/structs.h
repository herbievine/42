/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 11:39:52 by herbie            #+#    #+#             */
/*   Updated: 2023/06/21 07:51:25 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
#define STRUCTS_H

#include <sys/time.h>
#include <pthread.h>

typedef enum e_bool
{
	false,
	true
} t_bool;

typedef struct timeval t_timeval;

typedef struct s_fork
{
	pthread_mutex_t mutex;
	t_bool is_taken;
} t_fork;

typedef struct s_data
{
	int philo_count;
	int time_die_in_ms;
	int time_eat_in_ms;
	int time_sleep_in_ms;
	int max_eat;
	unsigned long start_time;
	t_bool is_game_over;
	pthread_mutex_t mutex;
} t_data;

typedef struct s_philo
{
	int id;
	t_bool is_eating;
	int eat_count;
	unsigned long last_meal_time;
	t_data *data;
	t_fork *left_fork;
	t_fork *right_fork;
	pthread_t thread;
} t_philo;

void ft_init_forks(t_fork *forks, t_data *data);
void ft_init_philos(t_philo *philos, t_data *data, t_fork *forks);
void ft_init_data(t_data *data);

#endif /* STRUCTS_H */