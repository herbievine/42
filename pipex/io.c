/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 15:28:45 by herbie            #+#    #+#             */
/*   Updated: 2023/03/27 19:21:12 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "io.h"
#include "structs.h"
#include "error.h"
#include "str.h"
#include "get_next_line.h"
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

int ft_get_infile(t_pipex *pipex, char **argv)
{
	int fd;
	char *buffer;

	if (pipex->here_doc)
	{
		fd = open(".here_doc", O_RDWR | O_CREAT | O_TRUNC, 0644);
		write(1, "heredoc> ", 9);
		while (fd > 0 && ft_read(0, &buffer) > 0)
		{
			if (ft_strncmp(buffer, argv[2], ft_strlen(argv[2])) == 0)
			{
				free(buffer);
				break;
			}
			write(fd, buffer, ft_strlen(buffer));
			free(buffer);
			write(1, "heredoc> ", 9);
		}
		close(fd);
		pipex->in_fd = open(".here_doc", O_RDONLY);
	}
	else
		pipex->in_fd = open(argv[1], O_RDONLY);
	return (pipex->in_fd);
}

int ft_get_outfile(t_pipex *pipex, char **argv, int argc)
{
	pipex->out_fd = open(argv[argc - 1], O_RDWR | O_CREAT | O_TRUNC, 0644);
	return (pipex->out_fd);
}