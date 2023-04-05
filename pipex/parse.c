/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 20:18:00 by herbie            #+#    #+#             */
/*   Updated: 2023/04/05 14:27:18 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "str.h"
#include "structs.h"
#include "io.h"
#include "split.h"
#include "error.h"
#include "free.h"
#include <stdio.h>
#include <unistd.h>

/**
 * @brief The ft_parse_args function takes in a pipex struct and the arguments
 * passed to the program. It then parses the arguments and sets the pipex
 * struct accordingly. It returns true if the arguments are valid, and false
 * otherwise.
 *
 * @param pipex
 * @param argc
 * @param argv
 * @return t_bool
 */
t_bool	ft_parse_args(t_pipex *pipex, int argc, char **argv)
{
	pipex->cmd_count = argc - 3 - pipex->here_doc;
	pipex->in_fd = -1;
	pipex->out_fd = -1;
	if (argv[1] && ft_strncmp(argv[1], "here_doc", 9) == 0)
		pipex->here_doc = true;
	else
		pipex->here_doc = false;
	if (argc < 5 + (int)pipex->here_doc)
		return (false);
	if (ft_get_infile(pipex, argv) == -1)
		return (false);
	if (ft_get_outfile(pipex, argv, argc) == -1)
		return (false);
	return (true);
}

/**
 * @brief The ft_parse_cmd_path function takes in a pipex struct and the
 * arguments passed to the program. It then parses the arguments and sets
 * `cmd_paths` in the pipex struct. It returns true if all the arguments were
 * parsed successfully, and false otherwise, freeing all memory created.
 *
 * @param pipex
 * @param argc
 * @param argv
 * @param envp
 * @return t_bool
 */
t_bool	ft_parse_cmd_path(t_pipex *pipex, int argc, char **argv, char **envp)
{
	int		i;
	char	**cmd;

	pipex->cmd_paths = malloc(sizeof(char *) * (argc - 2 - pipex->here_doc));
	if (!pipex->cmd_paths)
		return (false);
	i = 1 + pipex->here_doc;
	while (++i < argc - 1)
	{
		cmd = ft_split(argv[i], ' ');
		if (!cmd)
			return (ft_free_array(pipex->cmd_paths, i), false);
		pipex->cmd_paths[i - 2 - pipex->here_doc] = ft_find_path(cmd[0], envp);
	}
	return (true);
}

/**
 * @brief The ft_parse_cmd_args function takes in a pipex struct and the
 * arguments passed to the program. It then parses the arguments and sets
 * `cmd_args` in the pipex struct. It returns true if all the arguments were
 * parsed successfully, and false otherwise, freeing all memory created.
 *
 * @param pipex
 * @param argc
 * @param argv
 * @return t_bool
 */
t_bool	ft_parse_cmd_args(t_pipex *pipex, int argc, char **argv)
{
	int		i;
	char	**cmd;

	pipex->cmd_args = malloc(sizeof(char **) * (argc - 2 - pipex->here_doc));
	if (!pipex->cmd_args)
		return (false);
	i = 1 + pipex->here_doc;
	while (++i < argc - 1)
	{
		cmd = ft_split(argv[i], ' ');
		if (!cmd)
			return (ft_free_2d_array(pipex->cmd_args), false);
		pipex->cmd_args[i - 2 - pipex->here_doc] = cmd;
	}
	return (true);
}

/**
 * @brief The ft_get_infile function takes in a pipex struct and the arguments
 * passed to the program. It then parses the arguments and returns the full
 * program path.
 *
 * @param cmd
 * @param envp
 * @return char*
 */
char	*ft_find_path(char *cmd, char **envp)
{
	int		i;
	char	**paths;
	char	*path;
	char	*full_path;

	if (access(cmd, F_OK) == 0)
		return (cmd);
	i = -1;
	while (envp[++i])
		if (ft_strncmp("PATH=", envp[i], 5) == 0)
			paths = ft_split(envp[i] + 5, ':');
	i = -1;
	while (paths[++i])
	{
		path = ft_strjoin(paths[i], "/");
		full_path = ft_strjoin(path, cmd);
		free(path);
		if (access(full_path, F_OK) == 0)
			return (full_path);
		free(full_path);
	}
	ft_free_array(paths, -1);
	return (NULL);
}
