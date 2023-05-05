/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 09:54:31 by herbie            #+#    #+#             */
/*   Updated: 2023/05/05 11:17:13 by herbie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "io.h"
#include "str.h"
#include "structs.h"
#include "split.h"
#include "error.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

t_bool	ft_check_basic_rules(t_map *map);

void	ft_parse_map_or_throw(t_map *map, char *map_path)
{
	char	*buffer;
	int		fd;

	fd = open(map_path, O_RDONLY);
	if (fd < 0 || ft_read(&buffer, fd) < 0)
		ft_err(EUNKN, map);
	map->map = ft_split(buffer, '\n');
	if (!map->map || !ft_check_basic_rules(map))
		ft_err(EMAP, map);
}

t_bool	ft_check_basic_rules(t_map *map)
{
	int	i;

	i = -1;
	while (map->map[++i])
	{
		if (ft_strlen(map->map[i]) != ft_strlen(map->map[0]))
			return (false);
		if (ft_strchr(map->map[i], COLL))
			map->collectibles++;
		if (ft_strchr(map->map[i], EXIT))
			map->exits++;
		if (ft_strchr(map->map[i], STRT))
			map->entries++;
	}
	if (map->collectibles < 1 || map->exits != 1 || map->entries != 1)
		return (false);
	return (true);
}

// t_bool	ft_is_map_valid(char *map)
// {

// }
