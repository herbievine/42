/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/02 14:55:43 by herbie            #+#    #+#             */
/*   Updated: 2023/07/02 14:55:43 by herbie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "io.h"
#include "mem.h"
#include <unistd.h>

/**
 * @brief The ft_read function takes in a pointer to a string. It reads from
 * the file descriptor `fd` until it reaches the limiter character. It then
 * returns the number of characters read. If the file descriptor is invalid,
 * it returns -1.
 *
 * @param line
 * @param fd
 * @param limiter
 * @return int
 */
int	ft_read(char **line, int fd, char limiter)
{
	char	*buffer;
	char	c;
	int		i;

	i = 0;
	if (fd < 0)
		return (-1);
	buffer = ft_calloc(sizeof(char), BUFFER_SIZE);
	if (!buffer)
		return (-1);
	while (read(fd, &c, 1) > 0 && c && c != limiter && i < BUFFER_SIZE - 2)
		buffer[i++] = c;
	buffer[i] = '\n';
	buffer[i + 1] = '\0';
	*line = buffer;
	return (i + 1);
}
