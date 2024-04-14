/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcros <jcros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 09:56:16 by herbie            #+#    #+#             */
/*   Updated: 2024/04/10 12:42:00 by jcros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEXTURES_H
# define TEXTURES_H

# include "structs.h"
# include <stdbool.h>

# define TEXTURE_SIZE 64
# define TEXTURE_COUNT 4

# define FLOOR_PATH "./assets/floor.xpm"
# define WALL_PATH "./assets/wall.xpm"
# define PLAYER_PATH "./assets/cat.xpm"
# define COLLECTIBLE_PATH "./assets/fish.xpm"
# define EXIT_PATH "./assets/end.xpm"

void	ft_apply_texture(t_data *data, int x);
bool	ft_fill_map_config(t_map *map);
bool	ft_load_textures(t_data *data);

#endif /* TEXTURES_H */
