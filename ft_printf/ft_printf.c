/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 09:18:08 by hvine             #+#    #+#             */
/*   Updated: 2022/11/16 16:07:43 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_determine_num_args(const char *str);
static int ft_parse_special_chars(char c, void *arg);

/**
 * @brief The ft_printf() function formats and prints data. It returns the
 * number of characters printed (excluding the null byte used to end output to
 * strings).
 * 
 * @param format 
 * @param ... 
 * @return int 
 */
int	ft_printf(const char *format, ...)
{
	int bytes;
	va_list ap;

	bytes = 0;
	va_start(ap, ft_determine_num_args(format));
	while (*format)
	{
		if (*format != '%')
		{
			write(1, format++, 1);
			bytes++;
		}
		else if (*(++format) == '%')
		{
			write(1, format++, 1);
			bytes++;
		}
		else
		{
			bytes += ft_parse_special_chars(*format, va_arg(ap, void *));
			format++;
		}
	}
	va_end(ap);
	return (bytes);
}

static int	ft_determine_num_args(const char *str)
{
	int  acc;
	const char *set = "cspdiuxX%";

	acc = 0;
	while (*str)
	{
		if (*str == '%' && *(str + 1) && ft_strchr(set, *(str + 1)))
			acc++;
		str++;
	}

	return (acc);
}

static int ft_parse_special_chars(char c, void *arg)
{
	// ft_putstr_fd("parsing special char: ", 1);
	// ft_putchar_fd(c, 1);
	// ft_putstr_fd(" with arg: ", 1);
	// ft_putnbr_fd((int)arg, 1);
	// ft_putchar_fd('\n', 1);

	if (c == 'c')
		return (ft_putchar_fd((char)arg, 1));
	if (c == 's')
		return (ft_putstr_fd((char *)arg, 1));
	if (c == 'p')
		return (ft_putptr_fd((unsigned long)arg, 1));
	if (c == 'd' || c == 'i')
		return (ft_putnbr_fd((int)arg, 1));
	if (c == 'u')
		return (ft_putunbr_fd((unsigned int)arg, 1));
	if (c == 'x')
		return (ft_puthex_fd((unsigned int)arg, 1));
	if (c == 'X')
		return (ft_puthex_up_fd((unsigned int)arg, 1));
	return (0);
}
