/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subcommand.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 14:44:28 by herbie            #+#    #+#             */
/*   Updated: 2023/10/28 16:51:34 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SUBCOMMAND_H
# define SUBCOMMAND_H

# include "structs.h"
# include <stdbool.h>

bool	ft_create_subcommands(t_command *command , char **envp, char **cpy_envp);

#endif /* SUBCOMMAND_H */