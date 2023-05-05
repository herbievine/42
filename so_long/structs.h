/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 16:02:06 by herbie            #+#    #+#             */
/*   Updated: 2023/05/05 17:58:26 by herbie           ###   ########.fr       */
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
}		t_bool;

typedef struct s_map
{
	char	**map;
	int		width;
	int		height;
	int		collectibles;
	int		exits;
	int		entries;
	int		moves;
	t_bool	is_valid;
	t_bool	is_finished;
}		t_map;

#endif /* STRUCTS_H */