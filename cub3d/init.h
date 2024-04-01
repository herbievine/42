/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juliencros <juliencros@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 15:36:48 by juliencros        #+#    #+#             */
/*   Updated: 2024/04/01 15:16:55 by juliencros       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INIT_H
# define INIT_H

# include "structs.h"
# include <stdbool.h>

bool	ft_init_map(t_map *map);
bool	ft_resize_map(t_map *map, bool with_err);

#endif