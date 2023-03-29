/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 20:18:00 by herbie            #+#    #+#             */
/*   Updated: 2023/03/29 12:36:20 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "str.h"
#include "structs.h"
#include "io.h"
#include "split.h"
#include "error.h"
#include <stdio.h>
#include <unistd.h>

/**
 * @brief The parse_args function takes in a pipex struct and the arguments
 * passed to the program. It then parses the arguments and sets the pipex
 * struct accordingly. It returns true if the arguments are valid, and false
 * otherwise.
 *
 * @param pipex
 * @param argc
 * @param argv
 * @return t_bool
 */
t_bool parse_args(t_pipex *pipex, int argc, char **argv)
{
	if (argv[1] && ft_strncmp(argv[1], "here_doc", 9) == 0)
		pipex->here_doc = true;
	else
		pipex->here_doc = false;
	if (argc < 5 + pipex->here_doc)
		return (false);
	if (ft_get_infile(pipex, argv) == -1)
		return (false);
	if (ft_get_outfile(pipex, argv, argc) == -1)
		return (false);
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
