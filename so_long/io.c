/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 15:28:45 by herbie            #+#    #+#             */
/*   Updated: 2023/05/05 12:25:00 by herbie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "io.h"
#include "mem.h"
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

/**
 * @brief The ft_read function takes in a pointer to a string. It reads from
 * the file descriptor `fd` until it reaches the null terminator. It then
 * returns the number of bytes read.
 *
 * @param line
 * @param fd
 * @return int
 */
int ft_read(char **line, int fd)
{
	char *buffer;
	char c;
	int i;

	i = 0;
	if (fd < 0)
		return (-1);
	buffer = ft_calloc(sizeof(char), 100000);
	if (!buffer)
		return (-1);
	while (read(fd, &c, 1) > 0 && c && i < 100000 - 2)
		buffer[i++] = c;
	buffer[i] = '\n';
	buffer[i + 1] = '\0';
	*line = buffer;
	return (i + 1);
}

// char	**ft_fetch_map(char *map_path)
// {
// 	char	**map;
// 	char	*buffer;
// 	int		fd;
// 	int		i;

// 	fd = open(map_path, O_RDONLY);
// 	if (fd < 0)
// 		return (NULL);
// 	i = -1;
// 	while (ft_read(&buffer, fd) > 0)
// 		map[++i] = buffer;
// 	map[++i] = NULL;
// 	return (map);
// }
