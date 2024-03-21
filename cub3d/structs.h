/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 16:02:06 by herbie            #+#    #+#             */
/*   Updated: 2024/03/20 16:49:32 by herbie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include <stdbool.h>

# define WALL '1'
# define EMPT '0'

typedef enum e_cardinal_direction
{
	NORTH = 0,
	SOUTH = 1,
	WEST = 2,
	EAST = 3
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
	double	x;
	double	y;
	double	dx;
	double	dy;
	double	px;
	double	py;
	double	movespeed;
	double	rotspeed;
	bool	is_moving;
}	t_player;

typedef struct s_map
{
	char	**map;
	int		width;
	int		height;
}	t_map;

/**
 * @brief All the raycasting data
 * 
 * @param cx The camera plane
 * @param dx The direction x
 * @param dy The direction y
 * @param mx The map x
 * @param my The map y
 * @param sx The step x
 * @param sy The step y
 * @param sdx The side distance x
 * @param sdy The side distance y
 * @param ddx The delta distance x
 * @param ddy The delta distance y
 * @param wd The wall distance
 * @param side The side of the wall hit
 * @param h The height of the wall
 * @param ds The draw start
 * @param de The draw end
 */
typedef struct s_ray
{
	double	cx;
	double	dx;
	double	dy;
	int		mx;
	int		my;
	int		sx;
	int		sy;
	double	sdx;
	double	sdy;
	double	ddx;
	double	ddy;
	double	wd;
	int		side;
	int		h;
	int		ds;
	int		de;
}	t_ray;

typedef struct s_data
{
	void				*mlx_ptr;
	void				*win_ptr;
	t_texture			textures[4];
	// t_map				map;
	int					**map2;
	t_ray				ray;
	t_player		player;
	double			previous_frame_time;
	double			current_frame_time;
}	t_data;

#endif /* STRUCTS_H */
