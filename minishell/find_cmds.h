/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_cmds.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 15:12:26 by juliencros        #+#    #+#             */
/*   Updated: 2023/10/03 13:19:26 by herbie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FIND_CMDS_H
# define FIND_CMDS_H

# include "structs.h"
# include <stdbool.h>

bool	ft_set_path(t_subcommand *subcommand, t_token *token);

#endif