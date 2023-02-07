/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 14:22:02 by herbie            #+#    #+#             */
/*   Updated: 2023/02/07 18:16:03 by herbie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/**
 * @brief The ft_free function takes in a buffer and a string and returns a new
 * string that is the concatenation of the two. The buffer is freed.
 *
 * @param buffer
 * @param buf
 * @return char*
 */
char *ft_free(char *buffer, char *buf)
{
	char *temp;

	temp = ft_strjoin(buffer, buf);
	free(buffer);
	return (temp);
}

/**
 * @brief The ft_clean_buffer function takes in the buffer and returns
 * a new buffer with the first line removed. If the buffer is empty
 * or does not contain a newline, the buffer is freed and NULL is returned.
 *
 * @param buffer
 * @return char*
 */
char *ft_clean_buffer(char *buffer)
{
	char *tmp;

	if (!buffer[0] || ft_strchr(buffer, '\n') == NULL)
	{
		free(buffer);
		return NULL;
	}

	tmp = buffer;
	buffer = ft_strndup(
			buffer + (ft_strchr(buffer, '\n') - buffer + 1),
			ft_strlen((ft_strchr(buffer, '\n') + 1)));
	free(tmp);

	return buffer;
}

char *ft_extract_line_from_buffer(char *buffer)
{
	if (ft_strchr(buffer, '\n'))
		return ft_strndup(buffer, ft_strchr(buffer, '\n') - buffer + 1);
	else
		return ft_strndup(buffer, ft_strlen(buffer));
}

/**
 * @brief The get_line function takes in a file descriptor and the remains
 * of the buffer from the previous call to get_next_line. It reads the file
 * and returns the next line.
 *
 * @param fd
 * @param line
 * @return char*
 */
char *get_line(int fd, char *line)
{
	char *buffer;
	char *tmp;
	int bytes_out;

	if (!line)
		line = (char *)malloc(1);
	buffer = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer || !line)
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
		tmp = line;
		line = ft_strjoin(line, buffer);
		free(tmp);
		if (ft_strchr(line, '\n'))
			break;
	}
	free(buffer);
	return line;
}

/**
 * @brief The get_next_line function takes in a file descriptor and returns
 * the next line in the file.
 *
 * @param fd
 * @return char*
 */
char *get_next_line(int fd)
{
	static char *buffer;
	char *line;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
		return (NULL);
	buffer = get_line(fd, buffer);
	if (!buffer[0])
		line = NULL;
	else
		line = ft_extract_line_from_buffer(buffer);

	buffer = ft_clean_buffer(buffer);

	return (line);
}

int main()
{
	char *res;
	int fd = open("41_with_nl", O_RDONLY);

	for (int i = 0; i < 25; i++)
	{
		res = get_next_line(fd);
		printf("%s", res);
		if (res)
			free(res);
	}
}