/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 14:22:02 by herbie            #+#    #+#             */
/*   Updated: 2022/12/21 15:33:45 by herbie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char *ft_free(char *buffer, char *buf)
{
	char *temp;

	temp = ft_strjoin(buffer, buf);
	free(buffer);
	return (temp);
}

char *get_line(int fd, char *prev)
{
	char *buffer;
	char *tmp;
	int bytes_out;

	if (!prev)
		prev = (char *)malloc(1);
	buffer = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer || !prev)
		return (NULL);
	bytes_out = 1;
	while (bytes_out > 0)
	{
		bytes_out = read(fd, buffer, BUFFER_SIZE);
		if (bytes_out == -1)
		{
			free(buffer);
			return (NULL);
		}
		buffer[bytes_out] = 0;
		// tmp = prev;
		prev = ft_strjoin(prev, buffer);
		// free(tmp);
		if (ft_strchr(prev, '\n'))
			break;
	}

	free(buffer);
	return prev;
}

char *get_next_line(int fd)
{
	static char *buffer;
	char *line;

	if (BUFFER_SIZE <= 0)
		return (NULL);
	buffer = get_line(fd, buffer);
	if (!buffer || ft_strlen(buffer) == 0)
		return (NULL);
	line = ft_strdup(buffer);
	if (ft_strchr(line, '\n'))
	{
		line[ft_strchr(line, '\n') - line + 1] = 0;
		buffer += (ft_strchr(buffer, '\n') - buffer + 1);
	}
	else
	{
		buffer += ft_strlen(buffer);
		// free(buffer);
	}

	return (line);
}

int main()
{
	char *res;
	int fd = open("poem", O_RDONLY);

	for (int i = 0; i < 25; i++)
	{
		res = get_next_line(fd);
		printf("%s", res);
		// if (res)
		// 	free(res);
	}
}