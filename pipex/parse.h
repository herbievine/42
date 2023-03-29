/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 20:16:50 by herbie            #+#    #+#             */
/*   Updated: 2023/03/29 12:35:32 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
#define PARSE_H

#include "structs.h"

t_bool parse_args(t_pipex *pipex, int argc, char **argv);
char *ft_find_path(char *cmd, char **envp);

#endif /* PARSE_H */