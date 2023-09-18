/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_in_file.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juliencros <juliencros@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 15:02:08 by juliencros        #+#    #+#             */
/*   Updated: 2023/08/19 19:34:34 by juliencros       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FIND_IN_FILE_H
# define FIND_IN_FILE_H

# include "structs.h"
# include <stdbool.h>

bool	ft_find_in_file(t_token *token, t_subcommand *subcommand,
			t_subcommand *prev_subcommand);
bool	ft_set_in_fd(t_subcommand *subcommand, t_token *token,
			int token_length);

#endif