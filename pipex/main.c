/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 16:00:58 by herbie            #+#    #+#             */
/*   Updated: 2023/03/27 19:26:57 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"
#include "parse.h"
#include "error.h"
#include "get_next_line.h"
#include "str.h"
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
void ft_here_doc(t_pipex *pipex, char *limiter)
{
	char *line;
	pid_t reader;
	int fd[2];

	if (pipe(fd) == -1)
		return (perror("pipe"), (void)0);
	reader = fork();
	if (reader == -1)
		return (perror("fork"), (void)0);
	if (reader == 0)
	{
		close(fd[0]);
		write(STDOUT_FILENO, "heredoc> ", 9);
		while (ft_read(0, &line) > 0)
		{
			if (ft_strncmp(line, limiter, ft_strlen(limiter)) == 0)
			{
				free(line);
				break;
			}
			write(fd[1], line, ft_strlen(line));
			free(line);
			write(STDOUT_FILENO, "heredoc> ", 9);
		}
		close(fd[1]);
	}
	else
	{
		close(fd[1]);
		dup2(fd[0], STDERR_FILENO);
		close(fd[0]);
		waitpid(reader, NULL, 0);
	}
}

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

int main(int argc, char **argv, char **envp)
{
	t_pipex *pipex;

	(void)envp;
	pipex = malloc(sizeof(t_pipex));
	if (!pipex)
		return (1);
	if (!parse_args(pipex, argc, argv))
		return (cleanup(pipex), error(ERR_ARGS), 1);
	printf("in_fd: %d, out_fd: %d\n", pipex->in_fd, pipex->out_fd);
	return (cleanup(pipex), 0);

	// pipex = init_pipex(argc, argv);

	// if (!pipex)
	// 	return (1);

	// if (pipex->in_fd == -1 || pipex->out_fd == -1)
	// {
	// 	perror("open");
	// 	close(pipex->in_fd);
	// 	close(pipex->out_fd);
	// 	return (1);
	// }

	// printf("in_fd: %d, out_fd: %d\n", pipex->in_fd, pipex->out_fd);

	// close(pipex->in_fd);
	// close(pipex->out_fd);

	// free(pipex);

	// int fd[2];

	// if (pipe(fd) == -1)
	// {
	// 	perror("pipe");
	// 	return (1);
	// }

	// pid_t pid1 = fork();

	// if (pid1 == 0)
	// {
	// 	dup2(fd[1], STDOUT_FILENO);
	// 	close(fd[0]);
	// 	close(fd[1]);
	// 	execlp("ls", "ls", "-la", NULL);
	// }

	// pid_t pid2 = fork();

	// if (pid2 == 0)
	// {
	// 	dup2(fd[0], STDIN_FILENO);
	// 	close(fd[0]);
	// 	close(fd[1]);
	// 	execlp("grep", "grep", "herbie", NULL);
	// }

	// close(fd[0]);
	// close(fd[1]);

	// waitpid(pid1, NULL, 0);
	// waitpid(pid2, NULL, 0);

	// return (0);

	// if (argc == 5)
	// {
	// 	args = malloc(sizeof(t_args));
	// 	if (!args)
	// 		return (1);
	// 	args->file1 = argv[1];
	// 	args->file2 = argv[4];
	// 	args->cmd1 = argv[2];
	// 	args->cmd2 = argv[3];

	// 	// pid = fork();
	// 	// if (pid == 0)
	// 	// {
	// 	// 	printf("child\n");
	// 	// 	execve(args->file1, (char *const *)args->file1, NULL);
	// 	// }
	// 	// else
	// 	// {
	// 	// 	printf("parent\n");
	// 	// 	execve(args->cmd2, (char *const *)args->file2, NULL);
	// 	// }

	// 	free(args);
	// }
	// else
	// 	return (1);
	return (0);
}
