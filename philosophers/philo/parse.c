/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 11:46:55 by herbie            #+#    #+#             */
/*   Updated: 2023/05/21 15:27:32 by herbie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "int.h"
#include "structs.h"

/**
 * @brief The ft_parse_args function parses the command line arguments and
 * stores them in the data structure. If the arguments are invalid, it returns
 * false.
 * 
 * @param argc 
 * @param argv 
 * @param data 
 * @return t_bool 
 */
t_bool	ft_parse_args(int argc, char **argv, t_data *data)
{
	int	i;

	i = 0;
	while (++i < argc)
		if (!ft_isdigit_str(argv[i]))
			return (false);
	data->philo_count = ft_atoi(argv[1]);
	data->time_die_in_ms = ft_atoi(argv[2]);
	data->time_eat_in_ms = ft_atoi(argv[3]);
	data->time_sleep_in_ms = ft_atoi(argv[4]);
	if (argc == 6)
		data->max_eat = ft_atoi(argv[5]);
	if (data->philo_count < 1 || data->time_die_in_ms < 1
		|| data->time_eat_in_ms < 1 || data->time_sleep_in_ms < 1
		|| (argc == 6 && data->max_eat < 1))
		return (false);
	return (true);
}
