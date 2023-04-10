/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 16:00:58 by herbie            #+#    #+#             */
/*   Updated: 2023/04/10 14:38:55 by herbie           ###   ########.fr       */
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
	pipex->cmd_count = 0;
	pipex->cmd_paths = NULL;
	pipex->cmd_args = NULL;
	pipex->in_fd = -1;
	pipex->out_fd = -1;
}

t_bool	ft_exec_last_command(char *path, char **args, char **envp, int out_fd)
{
	pid_t	pid;
	int		fd[2];

	if (pipe(fd) == -1)
		return (false);
	pid = fork();
	if (pid == -1)
		return (false);
	if (pid == 0)
	{
		close(fd[0]);
		if (dup2(out_fd, STDOUT_FILENO) == -1)
			return (false);
		if (execve(path, args, envp) == -1)
			bash_not_found(args[0]);
		exit(0);
	}
	else
	{
		close(fd[1]);
		waitpid(pid, NULL, 0);
	}
	return (true);
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	*pipex;
	int		i;

	pipex = malloc(sizeof(t_pipex));
	if (!pipex)
		return (1);
	ft_init_pipex(pipex);
	if (!ft_parse_args(pipex, argc, argv))
		return (ft_cleanup(pipex), error(ERR_ARGS), 1);
	if (!ft_parse_cmd_path(pipex, argc, argv, envp))
		return (ft_cleanup(pipex), error(ERR_ARGS), 1);
	if (!ft_parse_cmd_args(pipex, argc, argv))
		return (ft_cleanup(pipex), error(ERR_ARGS), 1);
	if (dup2(pipex->in_fd, STDIN_FILENO) == -1)
		return (ft_cleanup(pipex), error(ERR_DUP), 1);
	i = -1;
	while (++i < pipex->cmd_count - 1)
		if (!ft_spawn_child(pipex->cmd_paths[i], pipex->cmd_args[i], envp))
			return (ft_cleanup(pipex), error(ERR_FORK), 1);
	ft_exec_last_command(pipex->cmd_paths[i], pipex->cmd_args[i], envp, pipex->out_fd);
	return (ft_cleanup(pipex), 0);
}
