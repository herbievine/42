// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   process.c                                          :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2023/03/29 11:14:55 by herbie            #+#    #+#             */
// /*   Updated: 2023/03/29 12:44:34 by codespace        ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

// #include "process.h"
// #include "structs.h"
// #include "error.h"
// #include "str.h"
// #include "parse.h"
// #include "split.h"
// #include <unistd.h>
// #include <stdlib.h>
// #include <stdio.h>
// #include <sys/wait.h>

// void ft_exec_cmds(t_pipex *pipex, char **argv, char **envp, int argc)
// {
// 	int i;

// 	// dup2(pipex->in_fd, STDIN_FILENO);
// 	i = 1 + pipex->here_doc;
// 	while (++i < argc - 2)
// 	{
// 		char **cmd = ft_split(argv[i], ' ');
// 		char *path = ft_find_path(cmd[0], envp);
// 		// debug
// 		printf("cmd: %s\n", cmd[0]);
// 		printf("path: %s\n", path);
// 		if (ft_spawn_child(pipex, cmd, path, envp) == -1)
// 			return;
// 	}
// 	// dup2(pipex->out_fd, STDOUT_FILENO);
// 	// char **cmd = ft_split(argv[i], ' ');
// 	// char *path = ft_find_path(cmd[0], envp);
// 	// if (execve(path, cmd, envp) == -1)
// 	// 	bash_not_found(cmd[0]);
// }

// int ft_spawn_child(t_pipex *pipex, char **cmd, char *path, char **envp)
// {
// 	pid_t pid;
// 	int fd[2];

// 	if (pipe(fd) == -1)
// 		return (cleanup(pipex), error(ERR_PIPE), -1);
// 	pid = fork();
// 	if (pid == -1)
// 		return (cleanup(pipex), error(ERR_FORK), -1);
// 	if (pid == 0)
// 	{
// 		close(fd[0]);
// 		dup2(fd[1], STDOUT_FILENO);
// 		if (execve(path, cmd, envp) == -1)
// 			bash_not_found(cmd[0]);
// 	}
// 	else
// 	{
// 		close(fd[1]);
// 		dup2(fd[0], STDIN_FILENO);
// 		waitpid(pid, NULL, 0);
// 	}
// 	return (0);
// }