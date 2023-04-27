/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 15:28:45 by herbie            #+#    #+#             */
/*   Updated: 2023/04/05 12:34:11 by herbie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "io.h"
#include "structs.h"
#include "error.h"
#include "str.h"
#include "print.h"
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

/**
 * @brief The ft_read function takes in a pointer to a string. It reads from
 * stdin until it reads a newline character or until it has read 10000
 * characters. It then returns the number of characters read, or -1 if an error
 * occurred.
 *
 * @param line
 * @return char*
 */
int	ft_read(char **line)
{
	char	*buffer;
	char	c;
	int		i;

	i = 0;
	buffer = malloc(sizeof(char) * 10000);
	if (!buffer)
		return (-1);
	while (read(0, &c, 1) > 0 && c && c != '\n' && i < 10000 - 2)
		buffer[i++] = c;
	buffer[i] = '\n';
	buffer[i + 1] = '\0';
	*line = buffer;
	return (i + 1);
}

/**
 * @brief The ft_handle_here_doc function takes in a string called limiter. It
 * opens a temporary file and writes to it until it reads the limiter string.
 * It then closes the file.
 * 
 * @param limiter 
 */
void	ft_handle_here_doc(char *limiter)
{
	int		fd;
	char	*buffer;

	fd = open(HERE_DOC_PATH, O_RDWR | O_CREAT | O_TRUNC, 0644);
	write(1, "heredoc> ", 9);
	while (fd > 0 && ft_read(&buffer) > 0)
	{
		if (ft_strncmp(buffer, limiter, ft_strlen(limiter)) == 0)
		{
			free(buffer);
			break ;
		}
		write(fd, buffer, ft_strlen(buffer));
		free(buffer);
		write(1, "heredoc> ", 9);
	}
	close(fd);
}

/**
 * @brief The ft_get_infile function takes in a pipex struct and the argv array.
 * It checks if the pipex struct has a here_doc flag. If it does, it opens a
 * file called "here_doc.txt" and writes to it until it reads the delimiter
 * string. It then closes the file and returns the file descriptor. If there is
 * no here_doc flag, it returns the file descriptor of the first argument.
 *
 * @param pipex
 * @param argv
 * @return int
 */
int	ft_get_infile(t_pipex *pipex, char **argv)
{
	if (pipex->here_doc)
	{
		ft_handle_here_doc(argv[2]);
		pipex->in_fd = open(HERE_DOC_PATH, O_RDONLY);
	}
	else
	{
		if (access(argv[1], F_OK) == -1)
		{
			pipex->is_invalid_input = true;
			ft_dprintf(2, "pipex: %s\n", ENOENT);
			pipex->in_fd = open(INVALID_INPUT_FILE_NAME,
					O_RDWR | O_CREAT | O_TRUNC, 0644);
		}
		else
		{
			pipex->is_invalid_input = false;
			pipex->in_fd = open(argv[1], O_RDONLY);
		}
	}
	return (pipex->in_fd);
}

/**
 * @brief The ft_get_outfile function takes in a pipex struct, the argv array,
 * and the argc. It checks if the pipex struct has a here_doc flag. If it does,
 * it opens the last argument in the argv array in append mode. If it doesn't,
 * it opens the last argument in the argv array in truncate mode. It then
 * returns the file descriptor.
 *
 * @param pipex
 * @param argv
 * @param argc
 * @return int
 */
int	ft_get_outfile(t_pipex *pipex, char **argv, int argc)
{
	if (pipex->here_doc)
		pipex->out_fd = open(argv[argc - 1], O_RDWR | O_CREAT | O_APPEND, 0644);
	else
		pipex->out_fd = open(argv[argc - 1], O_RDWR | O_CREAT | O_TRUNC, 0644);
	return (pipex->out_fd);
}
