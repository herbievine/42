/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 08:23:30 by herbie            #+#    #+#             */
/*   Updated: 2022/12/06 10:32:11 by herbie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

// char *get_next_line(int fd)
// {
// 	static char *buffer;

// 	if (fd < 0 || BUFFER_SIZE <= 0)
// 		return (0);
// }

char *ft_get_line(char *buffer, int fd)
{
	char *tmp;
	int bytes_out;

	bytes_out = 1;
	if (!buffer)
	{
		buffer = (char *)malloc(BUFFER_SIZE + 1);
		if (!buffer)
			return (0);
	}
	while (!ft_strchr(buffer, '\n') && bytes_out > 0)
	{
		tmp = buffer;
		buffer = ft_strjoin(buffer, (char *)malloc(BUFFER_SIZE + 1));
		free(tmp);
		if (!buffer)
			return (0);
		bytes_out = read(fd, buffer + ft_strlen(buffer), BUFFER_SIZE);
		if (bytes_out == -1)
			return (0);
		buffer[ft_strlen(buffer) + bytes_out] = '\0';
	}

	return (buffer);
}

char *get_next_line(int fd)
{
	static char *buffer;
	char *line;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
		return (0);
	buffer = ft_get_line(buffer, fd);
	if (buffer && ft_strchr(buffer, '\n'))
	{
		line = ft_strjoin("", buffer);
		line[ft_strchr(buffer, '\n') - buffer] = '\0';
		ft_strlcpy(buffer, ft_strchr(buffer, '\n') + 1, ft_strlen(ft_strchr(buffer, '\n') + 1) + 1);

		return line;
	}

	return (buffer);
}

int main()
{
	int fd = open("./test", O_RDONLY);
	printf("next line is '%s'\n", get_next_line(fd));
	printf("next line is '%s'\n", get_next_line(fd));
	printf("next line is '%s'\n", get_next_line(fd));
	printf("next line is '%s'\n", get_next_line(fd));
	printf("next line is '%s'\n", get_next_line(fd));
	printf("next line is '%s'\n", get_next_line(fd));
	printf("next line is '%s'\n", get_next_line(fd));
	printf("next line is '%s'\n", get_next_line(fd));
	// get_next_line(fd);
	// get_next_line(fd);
	// get_next_line(fd);
	// get_next_line(fd);
	// get_next_line(fd);
}
