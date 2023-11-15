/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subcommand.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juliencros <juliencros@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 14:44:28 by herbie            #+#    #+#             */
/*   Updated: 2023/11/04 13:36:34 by juliencros       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SUBCOMMAND_H
# define SUBCOMMAND_H

# include "structs.h"
# include <stdbool.h>

bool	ft_create_subcommands(t_command *command, char **env);

#endif /* SUBCOMMAND_H */