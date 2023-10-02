/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 18:04:18 by juliencros        #+#    #+#             */
/*   Updated: 2023/10/02 11:30:28 by herbie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "process.h"
#include "free.h"
#include <stdlib.h>
#include <stdio.h>
#include <strings.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <stdbool.h>
#include "str.h"
#include "mem.h"
#include "str2.h"
#include "token.h"

// # define SUBCOMMAND_FMT \
// 	"Subcommand(in_fd=%d, out_fd=%d, path='%s', \
// 	mode=%d, is_heredoc=%d)\n"
// # define SUBCOMMAND_ARG(subcommand) \
// 	subcommand.in_fd, subcommand.out_fd, subcommand.path, \
// 	subcommand.mode, subcommand.is_heredoc

// void	ft_print_subcommands(t_subcommand *subcommand)
// {
// 	t_subcommand	*head;

// 	head = subcommand;
// 	while (head)
// 	{
// 		t_subcommand tmp;
// 		ft_memcpy(&tmp, head, sizeof(t_subcommand));
// 		dprintf(2, SUBCOMMAND_FMT, SUBCOMMAND_ARG(tmp));
// 		head = head->next;
// 	}
// }

bool pipe_and_execute(t_subcommand *subcommand, int i, t_token **tokens);

bool ft_setup(t_subcommand *subcommand, int fd[2], int i, pid_t *pid)
{
	if (*pid == 0)
	{
		if (i == 0 && subcommand->in_fd != 0)
			printf("when = 0 dup2 = %d\n", dup2(subcommand->in_fd, STDIN_FILENO));
		if (!subcommand->next)
			printf("when lst dup2 = %d\n", dup2(subcommand->out_fd, STDOUT_FILENO));
		else
			dup2(fd[1], STDOUT_FILENO);
	}
	else
		dup2(fd[0], STDIN_FILENO);
	return (true);
}

bool ft_fork_and_pipe(t_subcommand *subcommand, int fd[2], pid_t *pid, int i)
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

	return (true);
}

bool pipe_and_execute(t_subcommand *subcommand, int i, t_token **tokens)
{
	pid_t pid;
	int fd[2];

	if (!ft_fork_and_pipe(subcommand, fd, &pid, i))
		return (printf("error fork and pipe\n"), false);
	if (!ft_setup(subcommand, fd, i, &pid))
		return (printf("error setup\n"), false);
	printf("[%d] before pid = %d\n", pid, pid);
	if (pid == PID_CHILD)
	{
		printf("[%d] in_fd = %d\n", pid, subcommand->in_fd);
		if (!subcommand->args)
		{
			execve(subcommand->path, NULL, NULL);
		}
		else
		{
			execve(subcommand->path, subcommand->args, g_env);
		}
		printf("[%d] after execve\n", pid);
		close(fd[0]);
		close(fd[1]);
		ft_clear_tokens(tokens);
		ft_free_subcommands(subcommand);
		exit(0);
	}
	else
	{
		close(fd[0]);
		close(fd[1]);
		int returnStatus;
		printf("[%d] prent waitiong pid = %d\n", pid, pid);
		waitpid(pid, &returnStatus, 0);
		printf("returnStatus = %d\n", returnStatus);
		printf("[%d] after waiting pid = %d\n", pid, pid);
		if (returnStatus == 0)
		{
			printf("The child process terminated normally.");
		}
		if (returnStatus == 1)
		{
			printf("The child process terminated with an error!.");
		}
	}
	return (true);
}

int ft_execution(t_subcommand *subcommand, t_token **tokens)
{
	int i;
	int j;
	t_subcommand *tmp;

	i = 0;
	j = 0;
	// subcommand->args = malloc(sizeof(char *) * 2);s
	// subcommand->args[0] = ft_strdup(subcommand->path);
	// printf ("subcommand->path = %s\n", subcommand->path);
	// ft_print_subcommands(subcommand);
	tmp = subcommand;
	while (tmp != NULL)
	{
		if (!pipe_and_execute(tmp, i, tokens))
			return (printf("pas bon\n"), false);
		dprintf(2, "tmp->path = %s\n", tmp->path);
		tmp = tmp->next;
		i++;
	}

	return (true);
}
