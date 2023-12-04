#include <stdio.h>
#include <stdlib.h>

int	main(int ac, char **av) {
  int		fd[2];
	int		pid;

	if (ac != 2)
		return (1);
	pipe(fd);
	pid = fork();
	if (pid == -1) {
		return (1);
	} else if (pid == 0) {
		close(1);
		dup2(fd[1], 1);
		close(fd[0]);
		close(fd[1]);
		execlp("./minishell/minishell", "./minishell/minishell", NULL);
	}
	wait(NULL);

  return (0);
}