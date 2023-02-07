/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 08:23:54 by herbie            #+#    #+#             */
/*   Updated: 2023/02/01 18:20:40 by herbie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
#define GET_NEXT_LINE_H

#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>

// #define DEBUG 1
// #if DEBUG
// #include "memory/memory.h"
// #endif

#ifndef BUFFER_SIZE
#define BUFFER_SIZE 5
#endif /* BUFFER_SIZE */

typedef struct line_s
{
	char *line;
	char *remainder;
} line_t;

char *get_next_line(int fd);
size_t ft_strlen(const char *s);
char *ft_strchr(const char *s, int c);
char *ft_strjoin(char const *s1, char const *s2);
char *ft_strndup(const char *s, size_t n);

#endif /* GET_NEXT_LINE_H */