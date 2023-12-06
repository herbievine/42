/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcros <jcros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 15:33:32 by herbie            #+#    #+#             */
/*   Updated: 2023/12/06 19:45:33 by jcros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# include "structs.h"
# include <stdbool.h>

bool	ft_parse(t_command *cmd, t_token *tokens, t_subcommand *subcommand);
bool	ft_is_io_symbol(t_token *token);
int		ft_check_pipe_valid(t_token *tokens);
int		ft_check_io_valid(t_token *token);

#endif /* PARSE_H */