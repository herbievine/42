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
			{
				mlx_destroy_image(data->mlx_ptr, data->textures[i]);
				free(data->textures[i]);
			}
			return (false);
		}
	}
	return (true);
}
