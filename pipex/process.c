/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 11:14:55 by herbie            #+#    #+#             */
/*   Updated: 2023/04/05 11:59:16 by herbie           ###   ########.fr       */
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
 * @brief The ft_spawn_child function takes in the cmd path, args, and envp and
 * spawns a child process to execute the command. It then waits for the child to
 * finish. If the fork or pipe fails, it returns false.
 *
 * @param path
 * @param args
 * @param envp
 * @return t_bool
 */
t_bool	ft_spawn_child(char *path, char **args, char **envp)
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
		dup2(fd[1], STDOUT_FILENO);
		if (execve(path, args, envp) == -1)
			bash_not_found(args[0]);
	}
	else
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		waitpid(pid, NULL, 0);
	}
	return (true);
}
