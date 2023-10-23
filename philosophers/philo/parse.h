/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 11:47:02 by herbie            #+#    #+#             */
/*   Updated: 2023/05/21 11:47:02 by herbie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# include "structs.h"
# include <stdbool.h>

bool	ft_parse_args(int argc, char **argv, t_data *data);

#endif /* PARSE_H */