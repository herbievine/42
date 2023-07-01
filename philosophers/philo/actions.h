/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 15:14:10 by herbie            #+#    #+#             */
/*   Updated: 2023/05/21 15:30:28 by herbie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ACTIONS_H
# define ACTIONS_H

# include "structs.h"

void	*ft_single_philo(void *arg);
void	*ft_multiple_philos(void *arg);
void	ft_print(t_philo *philo, char *msg, int arg_ms);
void	ft_eat(t_philo *philo);
void	ft_sleep_and_think(t_philo *philo);

#endif /* ACTIONS_H */