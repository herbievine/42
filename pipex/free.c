/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 12:41:40 by herbie            #+#    #+#             */
/*   Updated: 2023/04/05 14:49:53 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "free.h"
#include "structs.h"
#include "io.h"
#include <unistd.h>
#include <stdlib.h>

void ft_free_array(char **array, int size)
{
	int i;

	i = -1;
	if (size == -1)
		while (array[++i])
			free(array[i]);
	else
		while (++i < size)
			if (array[i])
				free(array[i]);
	free(array);
}

void ft_free_2d_array(char ***array)
{
	int i;

	i = -1;
	while (array[++i])
		ft_free_array(array[i], -1);
	free(array);
}

/**
 * @brief The ft_cleanup function takes in a pipex struct, closes all file
 * descriptors, and frees all memory.
 *
 * @param pipex
 */
void ft_cleanup(t_pipex *pipex)
{
	if (pipex->in_fd != -1)
		close(pipex->in_fd);
	if (pipex->out_fd != -1)
		close(pipex->out_fd);
	if (pipex->cmd_paths != NULL)
		ft_free_array(pipex->cmd_paths, pipex->cmd_count);
	if (pipex->cmd_args != NULL)
		ft_free_2d_array(pipex->cmd_args);
	if (pipex->here_doc)
		unlink(HERE_DOC_PATH);
	free(pipex);
}
