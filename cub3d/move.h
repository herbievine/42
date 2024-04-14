/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 11:13:57 by herbie            #+#    #+#             */
/*   Updated: 2024/03/07 11:13:57 by herbie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MOVE_H
# define MOVE_H

# include "structs.h"

void	ft_move_player_forward(t_data *data);
void	ft_move_player_backward(t_data *data);
void	ft_move_player_left(t_data *data);
void	ft_move_player_right(t_data *data);

#endif /* MOVE_H */