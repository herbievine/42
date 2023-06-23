/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 11:39:52 by herbie            #+#    #+#             */
/*   Updated: 2023/06/23 08:28:28 by codespace        ###   ########.fr       */
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

typedef struct s_data
{
	int philo_count;
	int time_die_in_ms;
	int time_eat_in_ms;
	int time_sleep_in_ms;
	int max_eat;
	unsigned long start_time;
	t_bool is_ready;
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
	pthread_mutex_t *left_fork;
	pthread_mutex_t *right_fork;
	pthread_t thread;
} t_philo;

void ft_init_forks(pthread_mutex_t *forks, t_data *data);
void ft_init_philos(t_philo *philos, t_data *data, pthread_mutex_t *forks);
void ft_init_data(t_data *data);

#endif /* STRUCTS_H */