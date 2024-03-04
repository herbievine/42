/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 09:56:16 by herbie            #+#    #+#             */
/*   Updated: 2023/05/08 09:56:16 by herbie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEXTURES_H
# define TEXTURES_H

# include "structs.h"

# define TILE_SIZE 48

# define FLOOR_PATH "./assets/floor.xpm"
# define WALL_PATH "./assets/wall.xpm"
# define PLAYER_PATH "./assets/cat.xpm"
# define COLLECTIBLE_PATH "./assets/fish.xpm"
# define EXIT_PATH "./assets/end.xpm"

t_bool	ft_load_textures(t_data *data);

#endif /* TEXTURES_H */
