/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 11:15:00 by herbie            #+#    #+#             */
/*   Updated: 2023/03/29 12:37:50 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROCESS_H
#define PROCESS_H

#include "structs.h"

void ft_exec_cmds(t_pipex *pipex, char **argv, char **envp, int argc);
int ft_spawn_child(t_pipex *pipex, char **cmd, char *path, char **envp);

#endif /* PROCESS_H */