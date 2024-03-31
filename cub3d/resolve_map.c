/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resolve_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcros <jcros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 18:08:49 by juliencros        #+#    #+#             */
/*   Updated: 2024/03/31 17:10:05 by jcros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "resolve_map.h"
#include <unistd.h>
#include <stdio.h>

static bool ft_move(t_data *data, char **copy_map, int way, char c);
static bool ft_move_backward(t_data *data, char **copy_map);
static bool	ft_find_character(t_data *data, char **copy_map, char c);

bool ft_resolve_map(t_data *data, char **copy_map)
{
	while (1)
	{
				if (ft_find_character(data, copy_map, ' ') 
			|| ft_find_character(data, copy_map, '\n') 
			|| ft_find_character(data, copy_map, '	')  
			|| !copy_map[data->map.row - 1][data->map.col] 
			|| !copy_map[data->map.row][data->map.col + 1] 
			|| !copy_map[data->map.row + 1] 
			|| !copy_map[data->map.row][data->map.col - 1])
			return (printf("error"), false);
		if (!ft_move(data, copy_map, 1, '0'))
		{
			if (!ft_move_backward(data, copy_map))
				break;
		}
	}
	return (true);
}

static bool ft_move(t_data *data, char **copy_map, int way, char c)
{
	if (way > 0)
		copy_map[data->map.row][data->map.col] = data->map.index;
	if (way < 0)
		copy_map[data->map.row][data->map.col] = '1';
	if (copy_map[data->map.row][data->map.col + 1] == c)
		data->map.col = data->map.col + 1;
	else if (copy_map[data->map.row + 1] && copy_map[data->map.row + 1][data->map.col] == c)
		data->map.row = data->map.row + 1;
	else if (copy_map[data->map.row - 1] && copy_map[data->map.row - 1][data->map.col] == c)
		data->map.row = data->map.row - 1;
	else if (copy_map[data->map.row][data->map.col - 1] == c)
		data->map.col = data->map.col - 1;
	else
		return (false);
	data->map.index += way;
	if (data->map.index == 'z')
		data->map.index = 'a';
	if (data->map.index == 'a' - 1)
		data->map.index = 'z';
	return (true);
}
static bool ft_move_backward(t_data *data, char **copy_map)
{
	if (ft_move(data, copy_map, -1, data->map.index - 1) == 0)
	{
		if (data->map.index == 'a')
			data->map.index = 'z';
		else
			data->map.index -= 1;
		return (true);
	}
	else if ((data->map.index == 'a' && ft_find_character(data, copy_map, 'z')))
	{
		ft_move(data, copy_map, -1, 'z');
		data->map.index = 'z';
	}
	if (!ft_move(data, copy_map, 1, '0')
		&& data->map.col == data->map.start_col && data->map.row == data->map.start_row)
		return (false);
	return (true);
}
static bool	ft_find_character(t_data *data, char **copy_map, char c)
{
	if (copy_map[data->map.row][data->map.col + 1] && copy_map[data->map.row][data->map.col + 1] == c)
		return (true);
	else if (copy_map[data->map.row + 1] && copy_map[data->map.row + 1][data->map.col] == c)
		return (true);
	else if (copy_map[data->map.row - 1] && copy_map[data->map.row - 1][data->map.col] == c)
		return (true);
	else if (copy_map[data->map.row][data->map.col - 1] && copy_map[data->map.row][data->map.col - 1] == c)
		return (true);
	else
		return (false);
}