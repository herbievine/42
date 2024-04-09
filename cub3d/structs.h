/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcros <jcros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 16:02:06 by herbie            #+#    #+#             */
/*   Updated: 2024/04/08 18:57:16 by jcros            ###   ########.fr       */
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

typedef struct s_img
{
	char	*path;
	void	*img;
	int		*addr;
	int		bpp;
	int		line_len;
	int		endian;
	int		width;
	int		height;
}	t_img;

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
	char					**char_map;
	char					*map_in_string;
	int						**map;
	int						str_index;
	int						width;
	int						height;
	void					*no_img;
	void					*so_img;
	void					*we_img;
	void					*ea_img;
	long					floor_hex;
	long					ceiling_hex;
	int						col;
	int						row;
	char					index;
	int						start_row;
	int						start_col;
	int						start_map;
	char					*path_texture[4];
	int						offset;
	t_cardinal_direction	start_dir;
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
 * @param wx The wall x
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
	double	wx;
}	t_ray;

typedef struct s_keypress
{
	bool	forward;
	bool	backward;
	bool	left;
	bool	right;
}	t_keypress;

typedef struct s_data
{
	void				*mlx_ptr;
	void				*win_ptr;
	int					*texture_buffer[4];
	int					**pixels;
	t_ray				ray;
	t_player			player;
	double				previous_frame_time;
	double				current_frame_time;
	t_map				map;
	int					fd;
	t_keypress			keypress;
}	t_data;

#endif /* STRUCTS_H */
