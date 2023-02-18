/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/18 15:43:42 by herbie            #+#    #+#             */
/*   Updated: 2023/02/18 16:09:27 by herbie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "display.h"
#include "strings.h"

static int ft_print_recursive(unsigned long n, char *base, int fd);

/**
 * @brief The ft_putchar_fd() function outputs the character 'c' to the given
 * file descriptor and returns the number of bytes written.
 *
 * @param c
 * @param fd
 * @return int
 */
int ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
	return (1);
}

/**
 * @brief The ft_putnbr_fd() function outputs the integer 'n' to the given
 * file descriptor and returns the number of bytes written.
 *
 * @param n
 * @param fd
 * @return int
 */
int ft_putnbr_fd(int n, int fd)
{
	long long num;

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
 * @brief The ft_putnbr_base_fd() function outputs the representation of the
 * unsigned integer 'n' in the given base to the given file descriptor and
 * returns the number of bytes written.
 *
 * @param n
 * @param base
 * @param fd
 * @return int
 */
int ft_putnbr_base_fd(unsigned long n, char *base, int fd)
{
	if (n == 0)
		return (ft_putchar_fd(base[0], fd));
	return (ft_print_recursive(n, base, fd) - 1);
}

static int ft_print_recursive(unsigned long n, char *base, int fd)
{
	int bytes;

	bytes = 1;
	if (n)
	{
		bytes += ft_print_recursive(n / ft_strlen(base), base, fd);
		ft_putchar_fd(base[n % ft_strlen(base)], fd);
	}
	return (bytes);
}
