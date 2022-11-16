/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 21:47:58 by herbie            #+#    #+#             */
/*   Updated: 2022/11/16 10:28:18 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdlib.h>
# include <unistd.h>
# include <stdarg.h>
# include <stdio.h>
# include <stdint.h>
# include <limits.h>

# ifndef __linux__
# define __linux__ 0
# endif /* __linux__ */

int	ft_printf(const char *, ...);

size_t	ft_strlen(const char *s);
int	ft_intlen(int n);
char	*ft_strchr(const char *s, int c);
int	ft_putnbr_fd(int n, int fd);
int	ft_putunbr_fd(unsigned int n, int fd);
int	ft_puthex_fd(unsigned long n, int fd);
int	ft_puthex_up_fd(long long n, int fd);
int ft_putptr_fd(unsigned long n, int fd);
int	ft_putnbr_base_fd(unsigned long n, char *base, int fd);
int	ft_putstr_fd(char *s, int fd);
int	ft_putchar_fd(char c, int fd);

#endif