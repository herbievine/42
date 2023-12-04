/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 18:04:34 by juliencros        #+#    #+#             */
/*   Updated: 2023/12/04 21:27:00 by herbie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROCESS_H
# define PROCESS_H

# include "structs.h"

# define READ 0
# define WRITE 1

int		ft_execute(t_command *command, char ***envp);
bool	ft_fork_and_pipe(t_command *command, t_subcommand *subcommand,
			pid_t *pid, int subcommand_length);
void	ft_redirect(t_subcommand *subcommand);

#endif