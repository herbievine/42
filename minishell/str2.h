/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str2.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 15:19:20 by juliencros        #+#    #+#             */
/*   Updated: 2023/10/28 10:59:13 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STR2_H
# define STR2_H

# include "structs.h"
# include <stdlib.h>

char	*ft_strdup(const char *s);
char	*ft_substr(char const *s, unsigned int start, size_t len);
int		ft_strschr(char *s1, char *s2);
int		ft_atoi(const char *str);
int		ft_position(char *str, char limitter);

#endif