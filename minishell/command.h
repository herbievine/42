/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 17:13:44 by herbie            #+#    #+#             */
/*   Updated: 2023/07/08 17:13:44 by herbie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMAND_H
# define COMMAND_H

# include "structs.h"
# include <stdbool.h>

t_command	ft_command_new(const char *raw);
bool		ft_append_token(t_command *command, t_token token);
bool		ft_clear_tokens(t_command *command);
void		ft_debug_print_command(t_command command);

#endif /* COMMAND_H */