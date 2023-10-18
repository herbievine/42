/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 16:00:58 by herbie            #+#    #+#             */
/*   Updated: 2023/06/23 08:29:55 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"
#include "parse.h"
#include "time.h"
#include "error.h"
#include "threads.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int	main(int argc, char *argv[])
{
	t_data			data;
	t_philo			*philos;
	pthread_mutex_t	*forks;

	if (argc < 5 || argc > 6)
		return (ft_err(EHELP));
	ft_init_data(&data);
	if (!ft_parse_args(argc, argv, &data))
		return (ft_err(EARGS));
	forks = malloc(sizeof(pthread_mutex_t) * data.philo_count);
	if (!forks)
		return (ft_err(EUNKN), 1);
	philos = malloc(sizeof(t_philo) * data.philo_count);
	if (!philos)
		return (ft_err(EUNKN), 1);
	ft_init_philos(philos, &data, forks);
	if (!ft_spawn_threads(&data, philos))
		return (ft_err(ETHRD));
	free(forks);
	return (0);
}
