/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 16:13:30 by herbie            #+#    #+#             */
/*   Updated: 2023/03/22 10:49:14 by herbie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STR_H
#define STR_H

#include <stdlib.h>

size_t ft_strlen(const char *s);
size_t ft_strlcpy(char *dst, const char *src, size_t size);
char *ft_strchr(const char *s, int c);
char *ft_strjoin(char const *s1, char const *s2);
char *ft_strndup(const char *s, size_t n);
int ft_strncmp(const char *s1, const char *s2, size_t n);

#endif /* STR_H */