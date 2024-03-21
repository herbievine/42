/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juliencros <juliencros@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 09:54:37 by herbie            #+#    #+#             */
/*   Updated: 2024/03/18 18:18:52 by juliencros       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# include "structs.h"
# include <stdbool.h>

// void	ft_init_map(t_data *data);
// void	ft_print_map(t_data data);
// void	ft_parse_map_or_throw(int **map, char *map_path);


bool	ft_fill_and_parse_data(char *argv[], t_data *data);

#endif /* PARSE_H */
