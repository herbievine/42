/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 16:00:58 by herbie            #+#    #+#             */
/*   Updated: 2023/04/05 12:32:54 by herbie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"
#include "parse.h"
#include "error.h"
#include "io.h"
#include "str.h"
#include "split.h"
#include "process.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <sys/wait.h>
#include <fcntl.h>

int	main(int argc, char **argv, char **envp)
{
	t_pipex	*pipex;
	int		i;

	pipex = malloc(sizeof(t_pipex));
	if (!pipex)
		return (1);
	if (!ft_parse_args(pipex, argc, argv))
		return (cleanup(pipex), error(ERR_ARGS), 1);
	if (!ft_parse_cmd_path(pipex, argc, argv, envp))
		return (cleanup(pipex), error(ERR_ARGS), 1);
	if (!ft_parse_cmd_args(pipex, argc, argv))
		return (cleanup(pipex), error(ERR_ARGS), 1);
	if (dup2(pipex->in_fd, STDIN_FILENO) == -1)
		return (cleanup(pipex), error(ERR_DUP), 1);
	i = -1;
	while (pipex->cmd_paths[++i] && pipex->cmd_paths[i + 1])
		if (!ft_spawn_child(pipex->cmd_paths[i], pipex->cmd_args[i], envp))
			return (cleanup(pipex), error(ERR_FORK), 1);
	if (dup2(pipex->out_fd, STDOUT_FILENO) == -1)
		return (cleanup(pipex), error(ERR_DUP), 1);
	if (execve(pipex->cmd_paths[i], pipex->cmd_args[i], envp) == -1)
		bash_not_found(pipex->cmd_args[i][0]);
	return (cleanup(pipex), 0);
}
