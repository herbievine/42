/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juliencros <juliencros@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 13:56:20 by juliencros        #+#    #+#             */
/*   Updated: 2023/12/04 19:51:11 by juliencros       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FREE_H
# define FREE_H

# include "structs.h"
# include <stdlib.h>

void	ft_free_all(t_command *command,
			bool do_you_want_to_free_the_env);
void	ft_free_subcommands(t_subcommand *subcommand);
void	ft_free_cmds(char **split, size_t j);
void	ft_free_array(char **array, int n);
void	ft_free_fd(int fd);

#endif
