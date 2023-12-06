/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 18:43:06 by herbie            #+#    #+#             */
/*   Updated: 2023/04/10 21:46:48 by herbie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "print.h"
#include "str.h"
#include "display.h"
#include <stdlib.h>
#include <unistd.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdint.h>
#include <limits.h>

static int	ft_parse_special_chars(char c, va_list *ap, int fd);

/**
 * @brief The ft_dprintf function formats and prints data. It returns the
 * number of characters printed (excluding the null byte used to end output to
 * strings).
 * 
 * @param fd
 * @param format 
 * @param ... 
 * @return int 
 */
int	ft_dprintf(int fd, const char *format, ...)
{
	int			bytes;
	va_list		ap;
	char		*legal_flags;

	bytes = 0;
	va_start(ap, format);
	legal_flags = "csdi%";
	while (*format)
	{
		if (*format == '%' && *(format + 1)
			&& ft_strchr((const char *)legal_flags, *(format + 1)))
		{
			bytes += ft_parse_special_chars(*++format, &ap, fd);
			format++;
		}
		else
			bytes += ft_putchar_fd(*format++, fd);
	}
	va_end(ap);
	return (bytes);
}

static int	ft_parse_special_chars(char c, va_list *ap, int fd)
{
	if (c == 'c')
		return (ft_putchar_fd(va_arg(*ap, int), fd));
	if (c == 's')
		return (ft_putstr_fd(va_arg(*ap, char *), fd));
	if (c == 'd' || c == 'i')
		return (ft_putnbr_fd(va_arg(*ap, int), fd));
	if (c == '%')
		return (ft_putchar_fd('%', fd));
	return (0);
}
