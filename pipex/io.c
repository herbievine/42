/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 15:28:45 by herbie            #+#    #+#             */
/*   Updated: 2023/03/27 15:39:26 by herbie           ###   ########.fr       */
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

t_bool get_infile(t_pipex *pipex, char **argv)
{
	int fd;
	char *buffer;

	if (pipex->here_doc)
	{
		fd = open(".here_doc", O_RDWR | O_CREAT | O_TRUNC, 0644);
		while (fd > 0)
		{
			write(1, "heredoc> ", 9);
			buffer = ft_get_next_line(0);
			if (!buffer)
				break;
			if (ft_strncmp(buffer, argv[2], ft_strlen(argv[2])) == 0)
				break;
			write(fd, buffer, ft_strlen(buffer));
			free(buffer);
		}
		close(fd);
		fd = open(".here_doc", O_RDONLY);
		if (fd < 0)
			return (false);
		pipex->in_fd = fd;
	}
	else
	{
		fd = open(argv[1], O_RDONLY);
		if (fd < 0)
			return (false);
		pipex->in_fd = fd;
	}

	return (true);
}

t_bool get_outfile(t_pipex *pipex, char **argv)
{
	return (true);
}