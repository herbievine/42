/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcros <jcros@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 09:54:37 by herbie            #+#    #+#             */
/*   Updated: 2024/04/10 10:24:29 by jcros            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# include "structs.h"
# include <stdbool.h>

bool	ft_fill_and_parse_data(char *argv[], t_data *data);
char	**ft_split_and_join_sep(const char *str, char sep);
bool	ft_check_map(t_map *map, char **parsed_line);
bool	ft_fill_and_parse_data(char *argv[], t_data *data);

#endif /* PARSE_H */
