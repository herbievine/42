/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 20:18:00 by herbie            #+#    #+#             */
/*   Updated: 2023/03/27 19:26:26 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "str.h"
#include "structs.h"
#include "io.h"
#include "error.h"
#include <stdio.h>

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
