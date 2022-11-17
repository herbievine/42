/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base_fd.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 10:06:32 by herbie            #+#    #+#             */
/*   Updated: 2022/11/17 17:35:15 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_print_recursive(unsigned long n, char *base, int fd);

/**
 * @brief The ft_putnbr_base_fd() function outputs the representation of the
 * unsigned integer 'n' in the given base to the given file descriptor and
 * returns the number of bytes written.
 * 
 * @param n 
 * @param base 
 * @param fd 
 * @return int 
 */
int	ft_putnbr_base_fd(unsigned long n, char *base, int fd)
{
	if (n == 0)
		return (ft_putchar_fd(base[0], fd));
	return (ft_print_recursive(n, base, fd) - 1);
}

static int	ft_print_recursive(unsigned long n, char *base, int fd)
{
	int	bytes;

	bytes = 1;
	if (n)
	{
		bytes += ft_print_recursive(n / ft_strlen(base), base, fd);
		ft_putchar_fd(base[n % ft_strlen(base)], fd);
	}
	return (bytes);
}
