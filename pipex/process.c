/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 11:14:55 by herbie            #+#    #+#             */
/*   Updated: 2023/04/10 15:28:22 by herbie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "process.h"
#include "structs.h"
#include "error.h"
#include "str.h"
#include "parse.h"
#include "split.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>

/**
 * @brief The ft_fork_and_pipe function forks and pipes the child process. If
 * the pipe fails, it returns -1.
 * 
 * @param fd 
 * @return pid_t 
 */
t_bool	ft_fork_and_pipe(int *fd, pid_t *pid)
{
	if (pipe(fd) == -1)
		return (false);
	*pid = fork();
	if (*pid == -1)
		return (false);
	return (true);
}

t_bool	ft_redirect(t_pipex *pipex, int *fd, int idx)
{
	if (idx == 0)
	{
		if (dup2(pipex->in_fd, STDIN_FILENO) == -1)
			return (false);
		if (dup2(fd[1], STDOUT_FILENO) == -1)
			return (false);
	}
	else if (idx == pipex->cmd_count - 1)
	{
		if (dup2(pipex->out_fd, STDOUT_FILENO) == -1)
			return (false);
		if (dup2(fd[0], STDIN_FILENO) == -1)
			return (false);
	}
	else
	{
		if (dup2(fd[0], STDIN_FILENO) == -1)
			return (false);
		if (dup2(fd[1], STDOUT_FILENO) == -1)
			return (false);
	}
	return (true);
}

/**
 * @brief The ft_spawn_child function takes in the cmd path, args, and envp and
 * spawns a child process to execute the command. It then waits for the child to
 * finish. If the fork or pipe fails, it returns false.
 *
 * @param path
 * @param args
 * @param envp
 * @return t_bool
 */
t_bool	ft_spawn_child(t_pipex *pipex, char **envp, int idx)
{
	pid_t	pid;
	int		fd[2];

	if (!ft_fork_and_pipe(fd, &pid))
		return (false);
	if (pid == 0)
	{
		close(fd[0]);
		if (idx == pipex->cmd_count - 1)
			dup2(pipex->out_fd, STDOUT_FILENO);
		else
			dup2(fd[1], STDOUT_FILENO);
		if (execve(pipex->cmd_paths[idx], pipex->cmd_args[idx], envp) == -1)
			bash_not_found(pipex->cmd_args[idx][0]);
		exit(0);
	}
	else
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		waitpid(pid, NULL, 0);
	}
	return (true);
}
