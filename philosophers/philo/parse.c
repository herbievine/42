/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 11:46:55 by herbie            #+#    #+#             */
/*   Updated: 2023/05/21 14:01:28 by herbie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "int.h"
#include "structs.h"

t_bool	ft_parse_args(int argc, char **argv, t_data *data)
{
	if (argc < 5 || argc > 6)
		return (false);
	data->philo_count = ft_atoi(argv[1]);
	data->time_die_in_ms = ft_atoi(argv[2]);
	data->time_eat_in_ms = ft_atoi(argv[3]);
	data->time_sleep_in_ms = ft_atoi(argv[4]);
	if (argc == 6)
		data->max_eat = ft_atoi(argv[5]);
	return (true);
}
