/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 16:02:06 by herbie            #+#    #+#             */
/*   Updated: 2023/05/07 12:18:42 by herbie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# define WALL '1'
# define EMPT '0'

typedef enum e_cardinal_direction
{
	NORTH = 1,
	SOUTH = 2,
	WEST = 3,
	EAST = 4
}	t_cardinal_direction;

typedef struct s_texture
{
	char	*path;
	void	*img;
	int		*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		width;
	int		height;
}	t_texture;

typedef struct s_player
{
	float	x;
	float	y;
	float	dx;
	float	dy;
	float	px;
	float	py;
	float movespeed;
	float rotspeed;
}	t_player;

typedef struct s_map
{
	char	**map;
	int		width;
	int		height;
}	t_map;

typedef struct s_data
{
	void				*mlx_ptr;
	void				*win_ptr;
	t_texture			textures[4];
	t_map				map;
	int					**map2;
	t_player		player;
	unsigned long long		previous_frame_time;
	unsigned long long		current_frame_time;
}	t_data;

#endif /* STRUCTS_H */
