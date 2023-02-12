/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 09:58:17 by herbie            #+#    #+#             */
/*   Updated: 2022/11/14 16:45:46 by herbie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

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
