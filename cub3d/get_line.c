/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_line.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juliencros <juliencros@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 14:22:52 by juliencros        #+#    #+#             */
/*   Updated: 2024/03/13 15:01:18 by juliencros       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_line.h"
#include "mem.h"

bool	ft_get_line(int fd, char **line)
{
	char	*buffer;
	char	c;
	int		i;

	i = 0;
	if (fd < 0 || !line)
		return (false);
	if (read(fd, &c, 1) <= 0)
	{
		*line = NULL;
		return (false);
	}
	buffer = ft_calloc(sizeof(char), BUFFER_SIZE);
	if (!buffer)
		return (false);
	buffer[i++] = c;
	while (read(fd, &c, 1) > 0 && c
		&& i < BUFFER_SIZE - 2 && c != '\n' && c != '\0')
		buffer[i++] = c;
	if (c == '\n')
		buffer[i++] = c;
	buffer[i] = '\0';
	*line = buffer;
	return (true);
}
