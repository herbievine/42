/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 08:23:30 by herbie            #+#    #+#             */
/*   Updated: 2022/11/19 08:46:45 by herbie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char *get_next_line(int fd)
{
	char *buffer;

	if (!fd)
		return (0);
	buffer = malloc((MAX_LINE_BUFFER - 1) * sizeof (char));
	if (!buffer)
		return (0);
	read(fd, buffer, MAX_LINE_BUFFER);
	printf("buffer: %s\n", buffer);

	return (buffer);
}
