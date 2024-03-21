/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juliencros <juliencros@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 20:34:59 by herbie            #+#    #+#             */
/*   Updated: 2024/03/14 18:25:06 by juliencros       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SPLIT_H
# define SPLIT_H

# include <stdlib.h>

char	**ft_split(char const *s, char c, int with_sep);
void	ft_free_list(char **list, size_t idx);

#endif /* SPLIT_H */
