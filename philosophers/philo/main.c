/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 16:00:58 by herbie            #+#    #+#             */
/*   Updated: 2023/05/22 10:57:05 by herbie           ###   ########.fr       */
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
	t_data	data;
	t_philo	*philos;
	t_fork	*forks;

	ft_init_data(&data);
	if (!ft_parse_args(argc, argv, &data))
		return (ft_err(EARGS));
	forks = malloc(sizeof(t_fork) * data.philo_count);
	if (!forks)
		return (ft_err(EUNKN), 1);
	ft_init_forks(forks, &data);
	philos = malloc(sizeof(t_philo) * data.philo_count);
	if (!philos)
		return (ft_err(EUNKN), 1);
	ft_init_philos(philos, &data, forks);
	data.start_time = ft_get_time_in_ms();
	if (!ft_spawn_threads(&data, philos))
		return (ft_err(EUNKN));
	free(forks);
	return (0);
}
