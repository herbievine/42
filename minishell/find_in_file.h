/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_in_file.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 15:02:08 by juliencros        #+#    #+#             */
/*   Updated: 2023/11/20 14:49:26 by herbie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FIND_IN_FILE_H
# define FIND_IN_FILE_H

# include "structs.h"
# include <stdbool.h>

bool	ft_set_infile(t_subcommand *subcommand, t_token *token);

#endif