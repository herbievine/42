/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcros <jcros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 13:38:05 by herbie            #+#    #+#             */
/*   Updated: 2024/04/08 18:02:46 by jcros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLAYER_H
# define PLAYER_H

# include "structs.h"

# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100

void	ft_init_player(t_player *player, t_data *data);

#endif