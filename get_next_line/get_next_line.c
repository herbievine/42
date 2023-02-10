/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 14:22:02 by herbie            #+#    #+#             */
/*   Updated: 2023/02/10 13:20:56 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/**
 * @brief The ft_calloc() function allocates memory for an array of nmemb
 * elements of size bytes each and returns a pointer to the allocated memory.
 * The memory is set to zero.
 * 
 * @param nmemb 
 * @param size 
 * @return void* 
 */
void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*space;
	size_t	i;

	if (size && nmemb > SIZE_MAX / size)
		return (0);
	space = malloc(nmemb * size);
	if (!space)
		return (0);
	i = 0;
	while (i < nmemb * size)
	{
		((char *)space)[i] = 0;
		i++;
	}
	return (space);
}

/**
 * @brief The ft_clean_buffer function takes in the buffer and returns
 * a new buffer with the first line removed. If the buffer is empty
 * or does not contain a newline, the buffer is freed and NULL is returned.
 *
 * @param buffer
 * @return char*
 */
char	*ft_clean_buffer(char *buffer)
{
	char	*tmp;

	if (!buffer[0] || ft_strchr(buffer, '\n') == NULL)
	{
		free(buffer);
		return (NULL);
	}
	tmp = buffer;
	buffer = ft_strndup(
			buffer + (ft_strchr(buffer, '\n') - buffer + 1),
			ft_strlen((ft_strchr(buffer, '\n') + 1)));
	free(tmp);
	if (!buffer)
		return (NULL);
	return (buffer);
}

/**
 * @brief The ft_extract_line_from_buffer function takes in the buffer and
 * returns a new string that is the first line in the buffer. If the buffer
 * does not contain a newline, the entire buffer is returned.
 * 
 * @param buffer 
 * @return char* 
 */
char	*ft_extract_line_from_buffer(char *buffer)
{
	if (ft_strchr(buffer, '\n'))
		return (ft_strndup(buffer, ft_strchr(buffer, '\n') - buffer + 1));
	else
		return (ft_strndup(buffer, ft_strlen(buffer)));
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
char	*get_line(int fd, char *line)
{
	char	*buffer;
	int		bytes_out;
	char	*tmp;

	if (!line)
		line = (char *)ft_calloc(1, 1);
	if (!line)
		return (NULL);
	buffer = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (free(line), NULL);
	bytes_out = 1;
	while (bytes_out > 0)
	{
		bytes_out = read(fd, buffer, BUFFER_SIZE);
		if (bytes_out == -1)
			return (free(buffer), NULL);
		buffer[bytes_out] = 0;
		tmp = line;
		line = ft_strjoin(line, buffer);
		free(tmp);
		if (ft_strchr(line, '\n'))
			break ;
	}
	return (free(buffer), line);
}

/**
 * @brief The get_next_line function takes in a file descriptor and returns
 * the next line in the file.
 *
 * @param fd
 * @return char*
 */
char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
		return (NULL);
	buffer = get_line(fd, buffer);
	if (!buffer[0])
		line = NULL;
	else
		line = ft_extract_line_from_buffer(buffer);
	if (!line)
		return (NULL);
	buffer = ft_clean_buffer(buffer);
	return (line);
}
