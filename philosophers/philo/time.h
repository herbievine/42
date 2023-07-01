/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 14:19:21 by herbie            #+#    #+#             */
/*   Updated: 2023/07/01 18:16:40 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TIME_H
# define TIME_H

# include "structs.h"

unsigned long	ft_get_time_in_ms(void);
int				ft_get_time_diff(unsigned long time);
int				ft_get_rounded_time_diff(unsigned long time, int round);
void			ft_usleep(unsigned long time);

#endif /* TIME_H */