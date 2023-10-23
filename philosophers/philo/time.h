/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 14:19:21 by herbie            #+#    #+#             */
/*   Updated: 2023/10/10 13:45:31 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TIME_H
# define TIME_H

# include <stdint.h>
# include "structs.h"

uint64_t	ft_get_unix_time(void);
int			ft_get_time_diff(uint64_t time);
void		ft_usleep(uint64_t time, t_data *data);

#endif /* TIME_H */