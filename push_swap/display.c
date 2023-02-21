/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 15:43:42 by herbie            #+#    #+#             */
/*   Updated: 2023/02/21 14:43:45 by herbie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "display.h"
#include "strings.h"
#include <unistd.h>

/**
 * @brief The ft_putchar_fd() function outputs the character 'c' to the given
 * file descriptor and returns the number of bytes written.
 *
 * @param c
 * @param fd
 * @return int
 */
int	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
	return (1);
}

/**
 * @brief The ft_putstr_fd() function outputs the string 's' to the given file
 * descriptor and returns the number of bytes written. If 's' is NULL, the
 * function writes "(null)" to the file descriptor and returns 6.
 *
 * @param s
 * @param fd
 * @return int
 */
int	ft_putstr_fd(char *s, int fd)
{
	if (!s)
		return (ft_putstr_fd("(null)", fd));
	write(fd, s, ft_strlen(s));
	return (ft_strlen(s));
}
