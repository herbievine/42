/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 15:28:45 by herbie            #+#    #+#             */
/*   Updated: 2023/04/29 16:59:44 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "io.h"
#include "structs.h"
#include "error.h"
#include "str.h"
#include "mem.h"
#include "print.h"
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

/**
 * @brief The ft_read function takes in a pointer to a string. It reads from
 * the file descriptor `fd` until it reaches the limiter character. It then
 * returns the number of characters read. If the file descriptor is invalid,
 * it returns -1.
 * 
 * @param line
 * @param fd
 * @param limiter
 * @return int
 */
int	ft_read(char **line, int fd, char limiter)
{
	char	*buffer;
	char	c;
	int		i;

	i = 0;
	if (fd < 0)
		return (-1);
	buffer = ft_calloc(sizeof(char), 10000);
	if (!buffer)
		return (-1);
	while (read(fd, &c, 1) > 0 && c && c != limiter && i < 10000 - 2)
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
	while (fd > 0 && ft_read(&buffer, STDIN_FILENO, '\n') > 0)
	{
		if (ft_strncmp(buffer, limiter, ft_strlen(limiter)) == 0
			&& ft_strlen(buffer) == ft_strlen(limiter) + 1)
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
 * @brief The ft_handle_urandom function takes in a pipex struct. It opens
 * /dev/urandom and reads from it until it reaches the null terminator. It then
 * writes the contents to a temporary file and closes it.
 */
void	ft_handle_urandom(void)
{
	int		tmp_fd;
	int		urandom_fd;
	char	*buffer;

	urandom_fd = open("/dev/urandom", O_RDONLY);
	if (urandom_fd < 0)
		return ;
	tmp_fd = open(URANDOM_PATH, O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (tmp_fd < 0)
		return ;
	if (ft_read(&buffer, urandom_fd, '\0') == -1)
		return ;
	write(tmp_fd, buffer, ft_strlen(buffer));
	free(buffer);
	close(tmp_fd);
}

/**
 * @brief The ft_get_infile function takes in a pipex struct and the argv array.
 * It checks if the pipex struct has a here_doc or is_urandom flag. If it does,
 * it calls the ft_handle_here_doc or ft_handle_urandom function respectively.
 * If it doesn't, it checks if the input file exists. If it does, it opens it
 * in read only mode. If it doesn't, it opens a temporary file in read only
 * mode and sets the is_invalid_input flag to true. It then returns the file
 * descriptor.
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
	else if (pipex->is_urandom)
	{
		ft_handle_urandom();
		pipex->in_fd = open(URANDOM_PATH, O_RDONLY);
	}
	else
	{
		if (access(argv[1], F_OK) == -1)
		{
			ft_dprintf(2, "pipex: %s\n", ENOENT);
			pipex->in_fd = open(INVALID_INPUT_PATH, O_RDONLY | O_CREAT, 0644);
			pipex->is_invalid_input = true;
		}
		else
			pipex->in_fd = open(argv[1], O_RDONLY);
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
