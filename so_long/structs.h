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
	t_bool	is_valid;
	t_bool	is_finished;
}	t_map;

#endif /* STRUCTS_H */