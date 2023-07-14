/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subcommand.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 14:44:28 by herbie            #+#    #+#             */
/*   Updated: 2023/07/14 14:44:28 by herbie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SUBCOMMANDS_H
# define SUBCOMMANDS_H

# include "structs.h"
# include <stdbool.h>

bool	ft_create_subcommands(t_command *command, t_token **tokens, int token_length);

#endif /* SUBCOMMANDS_H */