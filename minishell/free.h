/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juliencros <juliencros@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 13:56:20 by juliencros        #+#    #+#             */
/*   Updated: 2023/08/19 10:12:23 by juliencros       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FREE_H
# define FREE_H

# include "structs.h"
# include <stdlib.h>

void	ft_free_subcommands(t_subcommand *subcommand);
void	ft_free_cmds(char **split, size_t j);

#endif