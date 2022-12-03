/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvine <hvine@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 09:18:08 by hvine             #+#    #+#             */
/*   Updated: 2022/11/18 09:06:03 by hvine            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_is_legal_flag(const char *str);
static int	ft_parse_special_chars(char c, va_list *ap);

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
	int		bytes;
	va_list	ap;

	bytes = 0;
	va_start(ap, format);
	while (*format)
	{
		if (ft_is_legal_flag(format))
		{
			bytes += ft_parse_special_chars(*++format, &ap);
			format++;
		}
		else if (*format == '%' && *(format + 1) == '%')
		{
			bytes += ft_putchar_fd(*format++, 1);
			format++;
		}
		else
			bytes += ft_putchar_fd(*format++, 1);
	}
	va_end(ap);
	return (bytes);
}

static int	ft_is_legal_flag(const char *str)
{
	const char	*legal_flags = "cspdiuxX";

	if (*str == '%' && *(str + 1) && ft_strchr(legal_flags, *(str + 1)))
		return (1);
	return (0);
}

static int	ft_parse_special_chars(char c, va_list *ap)
{
	if (c == 'c')
		return (ft_putchar_fd(va_arg(*ap, int), 1));
	if (c == 's')
		return (ft_putstr_fd(va_arg(*ap, char *), 1));
	if (c == 'p')
		return (ft_putptr_fd(va_arg(*ap, void *), 1));
	if (c == 'd' || c == 'i')
		return (ft_putnbr_fd(va_arg(*ap, int), 1));
	if (c == 'u')
		return (ft_putunbr_fd(va_arg(*ap, unsigned int), 1));
	if (c == 'x')
		return (ft_puthex_fd(va_arg(*ap, unsigned int), 1));
	if (c == 'X')
		return (ft_puthex_up_fd(va_arg(*ap, unsigned int), 1));
	if (c == '%')
		return (ft_putchar_fd('%', 1));
	return (0);
}
