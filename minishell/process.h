/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juliencros <juliencros@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 18:04:34 by juliencros        #+#    #+#             */
/*   Updated: 2023/12/06 13:08:26 by juliencros       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROCESS_H
# define PROCESS_H

# include "structs.h"

# define READ 0
# define WRITE 1

int		ft_execute(t_command *command);
bool	ft_fork_and_pipe(t_command *command, t_subcommand *subcommand,
			pid_t *pid, int subcommand_nb);
void	ft_open_files(t_command *command,
			t_subcommand *subcommand, int subcommand_nb, bool dup);
int		parent_process(t_command *command,
			t_subcommand *subcommand, int return_status);

#endif
