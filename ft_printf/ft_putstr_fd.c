/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 10:00:27 by herbie            #+#    #+#             */
/*   Updated: 2022/11/15 18:59:30 by herbie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

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
