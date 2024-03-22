/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juliencros <juliencros@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 13:38:05 by herbie            #+#    #+#             */
/*   Updated: 2024/03/22 09:44:03 by juliencros       ###   ########.fr       */
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
void	ft_render_player(t_data *data);
void	ft_move_player(t_data *data, int key);

#endif