/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juliencros <juliencros@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 18:04:34 by juliencros        #+#    #+#             */
/*   Updated: 2023/12/03 16:46:28 by juliencros       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROCESS_H
# define PROCESS_H

# include "structs.h"

# define READ 0
# define WRITE 1

int		ft_execute(t_command *command, char ***envp);
bool	ft_fork_and_pipe(t_command *command, t_subcommand *subcommand,
			pid_t *pid, int subcommand_nb);
void	ft_redirect(t_subcommand *subcommand);

#endif