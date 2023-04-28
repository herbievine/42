/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 20:18:00 by herbie            #+#    #+#             */
/*   Updated: 2023/04/28 16:04:24 by herbie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "str.h"
#include "structs.h"
#include "io.h"
#include "split.h"
#include "error.h"
#include "free.h"
#include "env.h"
#include "mem.h"
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
	if (argv[1] && ft_strncmp(argv[1], "here_doc", 8) == 0
		&& ft_strlen(argv[1]) == 8)
		pipex->here_doc = true;
	else if (argv[1] && ft_strncmp(argv[1], "/dev/urandom", 12) == 0
		&& ft_strlen(argv[1]) == 12)
		pipex->is_urandom = true;
	if (argc < 5 + (int)pipex->here_doc)
		return (false);
	if (ft_get_infile(pipex, argv) == -1)
		return (false);
	if (ft_get_outfile(pipex, argv, argc) == -1)
		return (false);
	pipex->cmd_count = argc - 3 - pipex->here_doc;
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
t_bool	ft_parse_cmd_paths(t_pipex *pipex, int argc, char **argv, char **envp)
{
	int		i;
	char	**cmd;

	pipex->cmd_paths = ft_calloc(sizeof(char *), (argc - 2 - pipex->here_doc));
	if (!pipex->cmd_paths)
		return (false);
	i = 1 + pipex->here_doc;
	while (++i < argc - 1)
	{
		cmd = ft_split(argv[i], ' ');
		if (!cmd)
			return (ft_free_array(pipex->cmd_paths, i), false);
		pipex->cmd_paths[i - 2 - pipex->here_doc] = ft_find_path(cmd[0], envp);
		ft_free_array(cmd, -1);
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

	pipex->cmd_args = ft_calloc(sizeof(char **), (argc - 2 - pipex->here_doc));
	if (!pipex->cmd_args)
		return (false);
	i = 1 + pipex->here_doc;
	while (++i < argc - 1)
	{
		cmd = ft_split(argv[i], ' ');
		if (!cmd)
			return (ft_free_2d_array(pipex->cmd_args, pipex->cmd_count), false);
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
		return (ft_substr(cmd, 0, ft_strlen(cmd)));
	paths = ft_get_paths(envp);
	if (!paths)
		return (NULL);
	i = -1;
	while (paths[++i])
	{
		path = ft_strjoin(paths[i], "/");
		if (!path)
			return (ft_free_array(paths, -1), NULL);
		full_path = ft_strjoin(path, cmd);
		free(path);
		if (!full_path)
			return (ft_free_array(paths, -1), NULL);
		if (access(full_path, F_OK) == 0)
			return (ft_free_array(paths, -1), full_path);
		free(full_path);
	}
	return (ft_free_array(paths, -1), NULL);
}
