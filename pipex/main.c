/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 16:00:58 by herbie            #+#    #+#             */
/*   Updated: 2023/03/22 11:09:56 by herbie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"
#include "parse.h"
#include "error.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

int main(int argc, char **argv, char **envp)
{
	t_pipex pipex;

	(void)envp;
	if (!parse_args(&pipex, argc, argv))
		return (error(ERR_ARGS), 1);

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
