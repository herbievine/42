/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 13:55:47 by herbie            #+#    #+#             */
/*   Updated: 2023/05/21 13:56:01 by herbie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef THREADS_H
# define THREADS_H

# include "structs.h"
# include <stdbool.h>

bool	ft_spawn_threads(t_data *data, t_philo *philos);

#endif /* THREADS_H */
