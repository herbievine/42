/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 21:15:07 by herbie            #+#    #+#             */
/*   Updated: 2023/05/21 11:53:40 by herbie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "display.h"
#include "str.h"
#include <unistd.h>

static int	ft_print_recursive(unsigned long n, char *base, int fd);

/**
 * @brief The ft_putnbr_fd funtion outputs the integer 'n' to the given
 * file descriptor and returns the number of bytes written.
 * 
 * @param n 
 * @param fd 
 * @return int 
 */
int	ft_putnbr_fd(int n, int fd)
{
	long long	num;

	num = n;
	if (num < 0)
	{
		ft_putchar_fd('-', fd);
		num *= -1;
		return (ft_putnbr_base_fd(num, "0123456789", fd) + 1);
	}
	return (ft_putnbr_base_fd(num, "0123456789", fd));
}

/**
 * @brief The ft_putchar_fd function outputs the character 'c' to the given
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
 * @brief The ft_putstr_fd function outputs the string 's' to the given file
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

/**
 * @brief The ft_putnbr_base_fd funtion outputs the representation of the
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
