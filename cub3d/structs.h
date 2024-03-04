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

typedef struct s_player
{
	float	x;
	float	y;
	float	dx;
	float	dy;
	float	a;
}	t_player;

typedef struct s_map
{
	char	**map;
	int		width;
	int		height;
}	t_map;

typedef struct s_data
{
	void			*mlx_ptr;
	void			*win_ptr;
	t_player		player;
	t_map			map;
}	t_data;

#endif /* STRUCTS_H */
