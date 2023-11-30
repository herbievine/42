/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 10:59:36 by herbie            #+#    #+#             */
/*   Updated: 2023/04/10 21:55:15 by herbie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

# define EARGS "error: invalid arguments"
# define EUNKN "error: unknown error"
# define ETHRD "error: thread error"
# define EHELP "usage: ./philo <n_philos> <time_die>\
 <time_eat> <time_sleep> [max_eat]"

int		ft_err(char *err);

#endif /* ERROR_H */