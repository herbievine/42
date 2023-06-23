/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 14:19:21 by herbie            #+#    #+#             */
/*   Updated: 2023/05/21 14:19:21 by herbie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TIME_H
# define TIME_H

# include "structs.h"

unsigned long	ft_get_time_in_ms(void);
int				ft_get_time_diff_in_ms(unsigned long time);
void			ft_usleep(unsigned long time);

#endif /* TIME_H */