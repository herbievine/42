/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juliencros <juliencros@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 12:41:40 by herbie            #+#    #+#             */
/*   Updated: 2024/03/23 19:22:40 by juliencros       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "free.h"
#include "structs.h"
#include "mlx/mlx.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

/**
 * @brief The ft_free_array function takes in an array and frees all memory.
 * If n if provided, it will only free the memory of the first n elements.
 *
 * @param array
 * @param n
 */
void	ft_free_array(char **array, int n)
{
	int	i;

	i = -1;
	if (n == -1)
		while (array[++i])
			free(array[i]);
	else
		while (++i < n)
			if (array[i])
				free(array[i]);
	free(array);
}

void ft_free_array_int(int **array, int n)
{
	int	i;

	i = -1;
	if (n == -1)
		while (array[++i])
			free(array[i]);
	else
		while (++i < n)
			if (array[i])
				free(array[i]);
	free(array);
}

/**
 * @brief The ft_free_2d_array function takes in a 2d array and frees all
 * memory. If n if provided, it will only free the memory of the first n
 * elements.
 *
 * @param array
 */
void	ft_free_2d_array(char ***array, int n)
{
	int	i;

	i = -1;
	if (n == -1)
		while (array[++i])
			ft_free_array(array[i], -1);
	else
		while (++i < n)
			if (array[i])
				ft_free_array(array[i], -1);
	free(array);
}

/**
 * @brief The ft_free_textures function takes in a data struct and frees all
 * textures.
 * 
 * @param data 
 */
// void	ft_free_textures(t_data *data)
// {
// 	int	i;

// 	i = -1;
// 	while (++i < 5)
// 		if (data->textures[i])
// 			mlx_destroy_image(data->mlx_ptr, data->textures[i]);
// }

/**
 * @brief The ft_free_mlx function takes in a data struct and frees all mlx
 * related memory.
 * 
 * @param data 
 */
void	ft_free_mlx(t_data *data)
{
	if (data->mlx_ptr)
	{
		if (data->win_ptr)
			mlx_destroy_window(data->mlx_ptr, data->win_ptr);
		mlx_destroy_display(data->mlx_ptr);
		free(data->mlx_ptr);
	}
}

/**
 * @brief The ft_free_data function takes in a data struct and frees all
 * memory.
 *
 * @param data
 */
void	ft_free_data(t_data *data)
{
	if (data->fd > 0)
		close(data->fd);
	if (data->map.no_img != NULL)
		mlx_destroy_image(data->mlx_ptr, data->map.no_img);
	if (data->map.so_img != NULL)
		mlx_destroy_image(data->mlx_ptr, data->map.so_img);
	if (data->map.we_img != NULL)
		mlx_destroy_image(data->mlx_ptr, data->map.we_img);
	if (data->map.ea_img != NULL)
		mlx_destroy_image(data->mlx_ptr, data->map.ea_img);
	ft_free_mlx(data);
	if (data->map.char_map)
		ft_free_array(data->map.char_map, -1);
	if (data->map.map)
		ft_free_array_int(data->map.map, -1);
	if (data->map.map_in_string)
		free(data->map.map_in_string);
	if (data->map.path_texture)
		ft_free_array(data->map.path_texture, 5);
}
