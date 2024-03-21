/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juliencros <juliencros@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 15:36:48 by juliencros        #+#    #+#             */
/*   Updated: 2024/03/18 18:17:37 by juliencros       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INIT_H
# define INIT_H

# include "structs.h"
# include <stdbool.h>

void	ft_init(t_data *data);
int		ft_count_nl(t_map *map);
bool	ft_init_map(t_map *map);


#endif