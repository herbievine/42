/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fps.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcros <jcros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 14:04:38 by jcros             #+#    #+#             */
/*   Updated: 2024/04/10 10:52:35 by jcros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fps.h"
#include "structs.h"
#include "ints.h"
#include <stdlib.h>
#include <time.h>
#include <mlx.h>

void	ft_init_fps(t_data *data)
{
	int	i;

	i = -1;
	while (++i < MAX_FPS_AVG)
		data->fps.fps_avg[i] = 0;
	data->fps.current_frame_time = clock();
	data->fps.previous_frame_time = clock();
	data->fps.fps = 0;
	data->fps.fps_index = 0;
}

void	ft_calculate_fps(t_data *data)
{
	double	sum;
	int		i;
	double	frame_time;

	data->fps.previous_frame_time = data->fps.current_frame_time;
	data->fps.current_frame_time = clock();
	frame_time = (data->fps.current_frame_time - data->fps.previous_frame_time)
		/ CLOCKS_PER_SEC;
	data->player.movespeed = frame_time * 5;
	data->player.rotspeed = frame_time * 3;
	data->fps.fps = 1.0 / frame_time;
	sum = 0;
	data->fps.fps_avg[data->fps.fps_index++] = data->fps.fps;
	if (data->fps.fps_index >= MAX_FPS_AVG)
		data->fps.fps_index = 0;
	i = -1;
	while (++i < MAX_FPS_AVG)
	{
		if (data->fps.fps_avg[i] == 0)
			break ;
		sum += data->fps.fps_avg[i];
	}
	data->fps.fps = sum / i;
}

void	ft_render_fps(t_data *data)
{
	char	*fps_str;
	int		i;
	int		j;

	fps_str = ft_itoa(data->fps.fps);
	if (!fps_str)
		return ;
	i = 5;
	while (++i < 60)
	{
		j = -1;
		while (++j < 16)
			mlx_pixel_put(data->mlx_ptr, data->win_ptr, i, j, 0xFF0000);
	}
	mlx_string_put(
		data->mlx_ptr, data->win_ptr, 10, 12, 0xFFFFFF, "FPS: ");
	mlx_string_put(
		data->mlx_ptr, data->win_ptr, 35, 12, 0xFFFFFF, fps_str);
	free(fps_str);
}
