/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 13:56:20 by juliencros        #+#    #+#             */
/*   Updated: 2023/10/24 15:00:54 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FREE_H
# define FREE_H

# include "structs.h"
# include <stdlib.h>

void	ft_free_all(t_subcommand *subcommand, t_token **token,
			bool do_you_want_to_free_the_env);
void	ft_free_subcommands(t_subcommand *subcommand);
void	ft_free_cmds(char **split, size_t j);
void	ft_free_array(char **array, int n);
void	ft_free_fd(int fd);

#endif