/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_cmds.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juliencros <juliencros@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 15:12:26 by juliencros        #+#    #+#             */
/*   Updated: 2023/08/17 18:21:13 by juliencros       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FIND_CMDS_H
# define FIND_CMDS_H

# include "structs.h"
# include <stdbool.h>

bool	ft_set_cmd(t_token *token, t_subcommand *subcommand);

#endif