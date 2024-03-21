/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_line.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juliencros <juliencros@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 14:23:09 by juliencros        #+#    #+#             */
/*   Updated: 2024/03/11 10:19:14 by juliencros       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_LINE_H
# define GET_LINE_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>

# define BUFFER_SIZE 100000

bool	ft_get_line(int fd, char **line);

#endif