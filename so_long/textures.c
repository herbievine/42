/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 09:56:07 by herbie            #+#    #+#             */
/*   Updated: 2023/05/08 09:56:07 by herbie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "textures.h"
#include "structs.h"
#include "mlx/mlx.h"
#include <stdlib.h>

/**
 * @brief The ft_load_textures function loads the textures into the data struct.
 * If it fails to load a texture, it frees all the textures that were loaded
 * before and returns false.
 * 
 * @param data 
 * @return t_bool 
 */
t_bool	ft_load_textures(t_data *data)
{
	char	*texture_map[5];
	int		size;
	int		i;

	texture_map[0] = FLOOR_PATH;
	texture_map[1] = WALL_PATH;
	texture_map[2] = PLAYER_PATH;
	texture_map[3] = COLLECTIBLE_PATH;
	texture_map[4] = EXIT_PATH;
	i = -1;
	while (++i < 5)
	{
		data->textures[i] = mlx_xpm_file_to_image(
				data->mlx_ptr, texture_map[i], &size, &size);
		if (!data->textures[i])
		{
			while (--i >= 0)
				mlx_destroy_image(data->mlx_ptr, data->textures[i]);
			return (false);
		}
	}
	return (true);
}
