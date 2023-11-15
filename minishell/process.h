/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juliencros <juliencros@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 18:04:34 by juliencros        #+#    #+#             */
/*   Updated: 2023/11/15 15:36:36 by juliencros       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROCESS_H
# define PROCESS_H

# include "structs.h"

#define READ 0
#define WRITE 1

int		ft_execute(t_subcommand *subcommand, t_token **tokens);
bool	ft_fork_and_pipe(t_subcommand *subcommand,
	int fd[2], pid_t *pid);
void	ft_redirect(t_subcommand *subcommand);

#endif