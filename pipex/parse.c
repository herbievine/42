/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 20:18:00 by herbie            #+#    #+#             */
/*   Updated: 2023/03/22 11:14:37 by herbie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "str.h"
#include "structs.h"
#include "error.h"
#include <stdio.h>

t_bool parse_args(t_pipex *pipex, int argc, char **argv)
{
	printf("argc: %d, argv[1]: %s\n", argc, argv[1]);
	printf("compare: %d\n", ft_strncmp(argv[1], "here_doc", ft_strlen(argv[1])));
	if (argv[1] && ft_strncmp(argv[1], "here_doc", 9) == 0)
		pipex->here_doc = true;
	else
		pipex->here_doc = false;
	if (argc < 5 + pipex->here_doc)
		return (false);
	return (true);
}
