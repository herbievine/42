/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_out_file.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juliencros <juliencros@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 18:18:01 by juliencros        #+#    #+#             */
/*   Updated: 2023/08/17 19:09:14 by juliencros       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FIND_OUT_FILE_H
# define FIND_OUT_FILE_H

# include "structs.h"
# include <stdbool.h>

bool	ft_set_out_file(t_token *token, t_subcommand *subcommand);
bool	create_out_fd_without_gt(t_subcommand *subcommand);
bool	ft_set_out_fd(t_subcommand *subcommand,
			t_token	*token, int token_length);

#endif
