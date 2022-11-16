/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 09:18:08 by hvine             #+#    #+#             */
/*   Updated: 2022/11/16 11:22:51 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_determine_num_args(const char *str);
static int ft_parse_special_chars(char c, void *arg);

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
		else
		{
			bytes += ft_parse_special_chars(*(++format), va_arg(ap, void *));
			format++;
		}
	}
	va_end(ap);
	return (bytes);
}

int main()
{
	int i = 42;
	void *p = &i;
	
	printf("====================\n");

	ft_printf("%%%c%%%d%%\n", 'c', 42);

	printf("====================\n");


	// printf("====================\n");

	// // int a_char = printf("printing char: %c\n", 'a');
	// // printf("wrote %d bytes of data\n", a_char);
	// // int a_string = printf("printing string: %s\n", 0);
	// // printf("wrote %d bytes of data\n", a_string);
	// int a_pointer = printf("printing pointer: %p\n", p);
	// printf("wrote %d bytes of data\n", a_pointer);
	// // int a_decimal = printf("printing decimal: %d\n", 42);
	// // printf("wrote %d bytes of data\n", a_decimal);
	// // int a_unsigned_decimal = printf("printing unsigned decimal: %u\n", 42);
	// // printf("wrote %d bytes of data\n", a_unsigned_decimal);
	// int a_hex = printf("printing hex: %x\n", 42);
	// printf("wrote %d bytes of data\n", a_hex);
	// // int a_hex_upper = printf("printing hex upper: %X\n", 42);
	// // printf("wrote %d bytes of data\n", a_hex_upper);

	// printf("====================\n");
	
	// // int b_char = ft_printf("printing char: %c\n", 'a');
	// // printf("wrote %d bytes of data\n", b_char);
	// // int b_string = ft_printf("printing string: %s\n", 0);
	// // printf("wrote %d bytes of data\n", b_string);
	// int b_pointer = ft_printf("printing pointer: %p\n", p);
	// printf("wrote %d bytes of data\n", b_pointer);
	// // int b_decimal = ft_printf("printing decimal: %d\n", 42);
	// // printf("wrote %d bytes of data\n", b_decimal);
	// // int b_unsigned_decimal = ft_printf("printing unsigned decimal: %u\n", 42);
	// // printf("wrote %d bytes of data\n", b_unsigned_decimal);
	// int b_hex = ft_printf("printing hex: %x\n", 42);
	// printf("wrote %d bytes of data\n", b_hex);
	// // int b_hex_upper = ft_printf("printing hex upper: %X\n", 42);
	// // printf("wrote %d bytes of data\n", b_hex_upper);
	
	// printf("====================\n");
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
	write(1, "parsing special char: ", 22);
	write(1, &c, 1);
	write(1, "\n", 1);

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
	if (c == '%')	
		return (ft_putchar_fd('%', 1));
	return (0);
}
