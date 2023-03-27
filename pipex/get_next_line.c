/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 14:22:02 by herbie            #+#    #+#             */
/*   Updated: 2023/03/27 19:13:07 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "str.h"
#include "mem.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

/**
 * @brief The ft_read function takes in a file descriptor and a pointer to a
 * string. It reads the file descriptor and stores the contents in the string.
 * It returns the number of characters read.
 *
 * @param fd
 * @return char*
 */
int ft_read(int fd, char **line)
{
	char *buffer;
	char c;
	int i;

	i = 0;
	buffer = malloc(sizeof(char) * 10000);
	if (!buffer)
		return (-1);
	while (read(0, &c, 1) > 0 && c && c != '\n' && i < 10000)
		buffer[i++] = c;
	buffer[i] = '\n';
	buffer[i + 1] = '\0';
	*line = buffer;
	return (i + 1);
}
