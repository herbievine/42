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
# define COLL 'C'
# define EXIT 'E'
# define STRT 'P'

typedef enum e_bool
{
	false,
	true
}	t_bool;

typedef struct s_start
{
	int	x;
	int	y;
}	t_start;

typedef struct s_flood
{
	int	collectibles;
	int	exits;
}	t_flood;

typedef struct s_map
{
	char	**map;
	int		width;
	int		height;
	t_start	start;
	int		collectibles;
	int		exits;
	int		entries;
	int		moves;
}	t_map;

typedef struct s_assets
{
	void	*mlx_img;
}	t_assets;

typedef struct s_data
{
	void		*mlx_ptr;
	void		*win_ptr;
	void		*textures[5];
	t_map		*map;
}	t_data;

#endif /* STRUCTS_H */