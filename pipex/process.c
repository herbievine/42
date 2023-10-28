
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juliencros <juliencros@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 11:14:55 by herbie            #+#    #+#             */
/*   Updated: 2023/08/19 20:59:30 by juliencros       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "process.h"
#include "structs.h"
#include "error.h"
#include "str.h"
#include "print.h"
#include "free.h"
#include "parse.h"
#include "split.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>

/**
 * @brief The ft_fork_and_pipe function takes in a pointer to a pipex struct, a
 * pointer to an array of file descriptors, a pointer to a process id, and an
 * index. It then forks and pipes the file descriptors. If the fork fails, it
 * returns false.
 * 
 * @param pipex
 * @param fd
 * @param pid
 * @param idx
 * @return t_bool 
 */
t_bool	ft_fork_and_pipe(t_pipex *pipex, int fd[2], pid_t *pid, int idx)
{
	if (pipe(fd) == -1)
		return (false);
	*pid = fork();
	if (*pid == -1)
	{
		close(fd[0]);
		close(fd[1]);
		return (false);
	}
	if (*pid == 0)
	{
		if (idx == 0)
			dup2(pipex->in_fd, STDIN_FILENO);
		if (idx == pipex->cmd_count - 1)
			dup2(pipex->out_fd, STDOUT_FILENO);
		else
			dup2(fd[1], STDOUT_FILENO);
	}
	else
		dup2(fd[0], STDIN_FILENO);
	return (true);
}

/**
 * @brief The ft_spawn_child function takes in a pointer to a pipex struct, a
 * pointer to the environment variables, and an index. It then forks and pipes
 * the file descriptors. If the fork fails, it returns false. If the fork
 * succeeds, it executes the command. If the command is not found, it prints an
 * error message. It then cleans up and exits.
 * 
 * @param pipex
 * @param envp
 * @param idx
 * @return t_bool
 */
t_bool	ft_spawn_child(t_pipex *pipex, char **envp, int idx)
{
	pid_t	pid;
	int		fd[2];

	if (!ft_fork_and_pipe(pipex, fd, &pid, idx))
		return (false);
	if (pid == 0)
	{
		if (pipex->cmd_paths[idx])
			execve(pipex->cmd_paths[idx], pipex->cmd_args[idx], envp);
		else
			ft_dprintf(2, "pipex: %s: command not found\n",
				pipex->cmd_args[idx][0]);
		ft_cleanup(pipex);
		exit(0);
	}
	else
	{
		close(fd[1]);
		close(fd[0]);
	}
	return (true);
}
