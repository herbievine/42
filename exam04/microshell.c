/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   microshell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 15:29:41 by herbie            #+#    #+#             */
/*   Updated: 2024/04/16 13:53:09 by herbie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

void ft_err(char *str, char *reason)
{
	while (*str)
		write(2, str++, 1);
	if (reason)
		while (*reason)
			write(2, reason++, 1);
	write(2, "\n", 1);
}

void ft_exec(int argc, char *argv[], char *envp[], int tmp_fd)
{
    argv[argc] = NULL;
    dup2(tmp_fd, STDIN_FILENO);
    close(tmp_fd);
    execve(argv[0], argv, envp);
    ft_err("error: cannot execute ", argv[0]);
    exit(1);
}

void ft_cd(int argc, char *argv[])
{
	if (argc != 2)
		ft_err("error: cd: bad arguments", NULL);
	else if (chdir(argv[1]) != 0)
		ft_err("error: cd: cannot change directory to ", argv[1]);
}

int main(int argc, char *argv[], char *envp[])
{
	int i, tmp_fd, fd[2];

	(void)argc;
	i = 0;
	tmp_fd = dup(STDIN_FILENO);
	while (argv[i] && argv[i + 1])
	{
		argv = &argv[i + 1];
		i = 0;
		while (argv[i] && strcmp(argv[i], ";") && strcmp(argv[i], "|"))
			i++;
		if (strcmp(argv[0], "cd") == 0)
			ft_cd(i, argv);
		else if (i != 0 && (!argv[i] || strcmp(argv[i], ";") == 0))
		{
            if (fork() == 0)
                ft_exec(i, argv, envp, tmp_fd);
            else
            {
                close(tmp_fd);
                while (waitpid(-1, NULL, WUNTRACED) != -1)
                    ;
                tmp_fd = dup(STDIN_FILENO);
            }
        }
		else if (i != 0 && strcmp(argv[i], "|") == 0)
		{
			pipe(fd);
			if (fork() == 0)
			{
				dup2(fd[1], STDOUT_FILENO);
				close(fd[0]);
				close(fd[1]);
				ft_exec(i, argv, envp, tmp_fd);
			}
			else
			{
				close(fd[1]);
				close(tmp_fd);
				tmp_fd = fd[0];
			}
		}
	}
	close(tmp_fd);
	return (0);
}
