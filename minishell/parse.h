/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 15:33:32 by herbie            #+#    #+#             */
/*   Updated: 2023/10/03 12:56:38 by herbie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# include "structs.h"
# include <stdbool.h>

bool	ft_parse(t_token *token, t_subcommand *subcommand,
			t_subcommand *prev_subcommand);
bool	ft_is_io_symbol(t_token *token);

#endif /* PARSE_H */