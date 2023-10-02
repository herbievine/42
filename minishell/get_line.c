/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_line.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juliencros <juliencros@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 14:39:30 by juliencros        #+#    #+#             */
/*   Updated: 2023/08/17 18:40:31 by juliencros       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_line.h"
#include <stdio.h>
#include <unistd.h>

char	*ft_get_line(char *line, char limiter, int fd)
{
	int		i;
	char	buffer;

	i = 0;
	if (!line)
		return (NULL);
	while (read(fd, &buffer, 1) > 0 && buffer != limiter)
	{
		line[i] = buffer;
		i++;
	}
	line[i] = '\n';
	line[i + 1] = '\0';
	return (line);
}
