/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcros <jcros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 14:33:04 by herbie            #+#    #+#             */
/*   Updated: 2024/04/08 19:01:38 by jcros            ###   ########.fr       */
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
 * @brief The ft_move_player function handles the player movement. 
 * 
 * @param data 
 */
void	ft_move_player(t_data *data)
{
	if (data->keypress.forward)
		ft_move_player_forward(data);
	if (data->keypress.backward)
		ft_move_player_backward(data);
	if (data->keypress.left)
		ft_move_player_left(data);
	if (data->keypress.right)
		ft_move_player_right(data);
}

/**
 * @brief The ft_on_keypress function handles the keypresses. It checks if the
 * player has pressed the escape key or one of the movement keys.
 * 
 * @param keysym 
 * @param data 
 * @return int 
 */
int	ft_on_keypress(int keysym, t_data *data)
{
	data->player.is_moving = true;
	if (keysym == XK_Escape)
		ft_on_close(data);
	else if (keysym == XK_w)
		data->keypress.forward = true;
	else if (keysym == XK_s)
		data->keypress.backward = true;
	else if (keysym == XK_a)
		data->keypress.left = true;
	else if (keysym == XK_d)
		data->keypress.right = true;
	return (0);
}

/**
 * @brief The ft_on_keyrelease function handles the keyreleases. When the player
 * releases a movement key, we update the active keypress.
 * 
 * @param keysym 
 * @param data 
 * @return int 
 */
int	ft_on_keyrelease(int keysym, t_data *data)
{
	data->player.is_moving = false;
	if (keysym == XK_w)
		data->keypress.forward = false;
	if (keysym == XK_s)
		data->keypress.backward = false;
	if (keysym == XK_a)
		data->keypress.left = false;
	if (keysym == XK_d)
		data->keypress.right = false;
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
