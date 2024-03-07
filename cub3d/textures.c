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
#include <stdbool.h>

/**
 * @brief The ft_load_texture function loads the texture into the data struct.
 * If it fails to load a texture, it frees all the textures that were loaded
 * before and returns false.
 * 
 * @param data 
 * @return bool 
 */
bool	ft_load_texture(t_data *data, t_cardinal_direction dir, char *path)
{
	data->textures[dir].img = mlx_xpm_file_to_image(
			data->mlx_ptr,
			path,
			&data->textures[dir].width,
			&data->textures[dir].height);
	if (!data->textures[dir].img)
		return (false);
	return (true);
}
