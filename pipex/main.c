/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 16:00:58 by herbie            #+#    #+#             */
/*   Updated: 2023/03/29 13:06:48 by herbie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"
#include "parse.h"
#include "error.h"
#include "get_next_line.h"
#include "str.h"
#include "split.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <sys/wait.h>
#include <fcntl.h>

/**
 * @brief The ft_here_doc function takes in a pipex struct and reads from stdin
 * until it reaches the limiter string. It then pipes the contents to the next
 * command.
 *
 * @param pipex
 */
// void ft_here_doc(t_pipex *pipex, char *limiter)
// {
// 	char *line;
// 	pid_t reader;
// 	int fd[2];

// 	if (pipe(fd) == -1)
// 		return (perror("pipe"), (void)0);
// 	reader = fork();
// 	if (reader == -1)
// 		return (perror("fork"), (void)0);
// 	if (reader == 0)
// 	{
// 		close(fd[0]);
// 		write(STDOUT_FILENO, "heredoc> ", 9);
// 		while (ft_read(0, &line) > 0)
// 		{
// 			if (ft_strncmp(line, limiter, ft_strlen(limiter)) == 0)
// 			{
// 				free(line);
// 				break;
// 			}
// 			write(fd[1], line, ft_strlen(line));
// 			free(line);
// 			write(STDOUT_FILENO, "heredoc> ", 9);
// 		}
// 		close(fd[1]);
// 	}
// 	else
// 	{
// 		close(fd[1]);
// 		dup2(fd[0], STDERR_FILENO);
// 		close(fd[0]);
// 		waitpid(reader, NULL, 0);
// 	}
// }

/**
 * @brief The cleanup function takes in a pipex struct, closes all file
 * descriptors, and frees all memory.
 *
 * @param pipex
 */
void cleanup(t_pipex *pipex)
{
	if (pipex->in_fd != -1)
		close(pipex->in_fd);
	if (pipex->out_fd != -1)
		close(pipex->out_fd);
	free(pipex);
}

char *ft_find_path(char *cmd, char **envp)
{
	int i;
	char **paths;

	i = -1;
	while (envp[++i])
		if (ft_strncmp("PATH=", envp[i], 5) == 0)
			paths = ft_split(envp[i] + 5, ':');
	i = -1;
	while (paths[++i])
	{
		char *path = ft_strjoin(paths[i], "/");
		char *full_path = ft_strjoin(path, cmd);
		free(path);
		if (access(full_path, F_OK) == 0)
			return (full_path);
		free(full_path);
	}
	//! FIX FREE(paths)
	return (NULL);
}

int main(int argc, char **argv, char **envp)
{
	t_pipex *pipex;
	int i;
	int fd[2];
	pid_t pid;

	(void)envp;
	pipex = malloc(sizeof(t_pipex));
	if (!pipex)
		return (1);
	if (!parse_args(pipex, argc, argv))
		return (cleanup(pipex), error(ERR_ARGS), 1);

	// DEBUG
	// i = 1 + pipex->here_doc;
	// printf("----------------\n");
	// while (++i < argc - 1)
	// {
	// 	char **cmd = ft_split(argv[i], ' ');
	// 	char *path = ft_find_path(cmd[0], envp);
	// 	printf("path -> %s\n", path);
	// 	int j = 0;
	// 	while (cmd[j])
	// 	{
	// 		printf("cmd[%d] -> %s\n", j, cmd[j]);
	// 		j++;
	// 	}
	// 	printf("----------------\n");
	// }
	// END DEBUG

	dup2(pipex->in_fd, STDIN_FILENO);
	i = 1 + pipex->here_doc;
	while (++i < argc - 2)
	{
		// init pipe
		if (pipe(fd) == -1)
			return (cleanup(pipex), error(ERR_PIPE), 1);
		// fork program
		pid = fork();
		if (pid == -1)
			return (cleanup(pipex), error(ERR_FORK), 1);
		// child process
		if (pid == 0)
		{
			// close pipe
			close(fd[0]);
			// redirect stdout
			dup2(fd[1], STDOUT_FILENO);
			// execute program
			char **cmd = ft_split(argv[i], ' ');
			char *path = ft_find_path(cmd[0], envp);
			if (execve(path, cmd, envp) == -1)
				return (cleanup(pipex), bash_not_found(cmd[0]), 1);
		}
		// parent process
		else
		{
			// close pipe
			close(fd[1]);
			// redirect stdin
			dup2(fd[0], STDIN_FILENO);
			// wait for child process to finish
			waitpid(pid, NULL, 0);
		}
	}
	// redirect stdout
	dup2(pipex->out_fd, STDOUT_FILENO);
	// execute last program
	char **cmd = ft_split(argv[i], ' ');
	char *path = ft_find_path(cmd[0], envp);
	if (execve(path, cmd, envp) == -1)
		return (cleanup(pipex), bash_not_found(cmd[0]), 1);
	return (cleanup(pipex), 0);
}
