/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 16:00:58 by herbie            #+#    #+#             */
/*   Updated: 2023/04/27 19:09:02 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"
#include "parse.h"
#include "error.h"
#include "io.h"
#include "str.h"
#include "split.h"
#include "process.h"
#include "free.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <sys/wait.h>
#include <fcntl.h>

void	ft_init_pipex(t_pipex *pipex)
{
	pipex->in_fd = -1;
	pipex->out_fd = -1;
	pipex->here_doc = false;
	pipex->is_invalid_input = false;
	pipex->cmd_paths = NULL;
	pipex->cmd_args = NULL;
	pipex->cmd_count = 0;
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	*pipex;
	int		i;

	pipex = malloc(sizeof(t_pipex));
	if (!pipex)
		return (EXIT_FAILURE);
	ft_init_pipex(pipex);
	if (!ft_parse_args(pipex, argc, argv))
		return (ft_cleanup(pipex), ft_err(EARGS));
	if (!ft_parse_cmd_paths(pipex, argc, argv, envp))
		return (ft_cleanup(pipex), ft_err(EARGS));
	if (!ft_parse_cmd_args(pipex, argc, argv))
		return (ft_cleanup(pipex), ft_err(EARGS));
	i = -1;
	while (++i < pipex->cmd_count)
		if (!ft_spawn_child(pipex, envp, i))
			return (ft_cleanup(pipex), ft_err(EUNKN));
	i = -1;
	while (++i < pipex->cmd_count)
		wait(NULL);
	return (ft_cleanup(pipex), 0);
}
