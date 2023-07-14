/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 17:13:44 by herbie            #+#    #+#             */
/*   Updated: 2023/07/13 17:40:39 by herbie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMAND_H
# define COMMAND_H

# include "structs.h"
# include <stdbool.h>

t_command	ft_command_new(void);

bool	ft_create_commands_from_pipes(t_token **token_list, int token_length);
void	ft_debug_print_command(t_token *token_list, int token_length);

#endif /* COMMAND_H */