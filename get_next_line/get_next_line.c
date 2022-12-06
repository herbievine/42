/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 08:23:30 by herbie            #+#    #+#             */
/*   Updated: 2022/12/06 11:33:37 by herbie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define BUFFER_SIZE 1024

char *get_line(int fd)
{
	char *buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return NULL;

	int bytes_read = 0;
	int pos = 0;
	int line_len = 0;

	while (1)
	{
		bytes_read = read(fd, buffer + pos, BUFFER_SIZE - pos);
		if (bytes_read == -1)
		{
			free(buffer);
			return NULL;
		}

		pos += bytes_read;
		buffer[pos] = '\0';

		char *newline = strchr(buffer, '\n');
		if (newline)
		{
			line_len = newline - buffer;
			char *line = malloc(line_len + 1);
			if (!line)
			{
				free(buffer);
				return NULL;
			}
			strncpy(line, buffer, line_len);
			line[line_len] = '\0';

			memmove(buffer, newline + 1, pos - line_len - 1);
			pos -= line_len + 1;

			return line;
		}

		if (bytes_read == 0)
		{
			if (pos == 0)
			{
				free(buffer);
				return NULL;
			}
			else
			{
				char *line = malloc(pos + 1);
				if (!line)
				{
					free(buffer);
					return NULL;
				}
				strncpy(line, buffer, pos);
				line[pos] = '\0';

				return line;
			}
		}

		char *new_buffer = realloc(buffer, pos + BUFFER_SIZE + 1);
		if (!new_buffer)
		{
			free(buffer);
			return NULL;
		}
		buffer = new_buffer;
	}
}

int main()
{
	int fd = open("./test", O_RDONLY);
	printf("next line is '%s'\n", get_line(fd));
	printf("next line is '%s'\n", get_line(fd));
	printf("next line is '%s'\n", get_line(fd));
	printf("next line is '%s'\n", get_line(fd));
	printf("next line is '%s'\n", get_line(fd));
	printf("next line is '%s'\n", get_line(fd));
	printf("next line is '%s'\n", get_line(fd));
	printf("next line is '%s'\n", get_line(fd));
}
