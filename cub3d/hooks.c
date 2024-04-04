/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcros <jcros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 14:33:04 by herbie            #+#    #+#             */
/*   Updated: 2024/04/04 14:00:52 by jcros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hooks.h"
#include "structs.h"
#include "window.h"
#include "free.h"
#include "move.h"
#include "mlx/mlx.h"
#include <stdlib.h>
#include <stdio.h>
#include <X11/keysym.h>

/**
 * @brief The ft_handle_move function handles the movement of the player. It
 * checks if the player is moving into a wall, and if not, it moves the player
 * and increments the move counter.
 * 
 * @param keysym 
 * @param data 
 */
void	ft_handle_move(int keysym, t_data *data)
{
	data->player.is_moving = true;
	if (keysym == XK_w)
		ft_move_player_forward(data);
	else if (keysym == XK_s)
		ft_move_player_backward(data);
	else if (keysym == XK_a)
		ft_move_player_left(data);
	else if (keysym == XK_d)
		ft_move_player_right(data);
}

/**
 * @brief The ft_on_keypress function handles the keypresses. It checks if the
 * player has pressed the escape key, and if so, it calls the ft_on_close
 * function. Otherwise, it calls the ft_handle_move function. It also handles
 * the win condition.
 * 
 * @param keysym 
 * @param data 
 * @return int 
 */
int	ft_on_keypress(int keysym, t_data *data)
{
	if (keysym == XK_Escape)
		ft_on_close(data);
	else
		ft_handle_move(keysym, data);
	return (0);
}

int	ft_on_keyrelease(int keysym, t_data *data)
{
	data->player.is_moving = false;
	(void)keysym;
	(void)data;
	return (0);
}

/**
 * @brief The ft_on_close function frees the textures, mlx, and data, and then
 * exits the program.
 * 
 * @param data 
 * @return int 
 */
int	ft_on_close(t_data *data)
{
	ft_free_data(data);
	exit(0);
	return (0);
}
