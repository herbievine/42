/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: herbie <herbie@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 21:47:58 by herbie            #+#    #+#             */
/*   Updated: 2022/11/15 08:47:52 by herbie           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdlib.h>
# include <unistd.h>
# include <stdarg.h>
# include <stdio.h>
# include <stdint.h>

int	ft_printf(const char *, ...);

size_t	ft_strlen(const char *s);
int	ft_intlen(int n);
char	*ft_strchr(const char *s, int c);
int	ft_putnbr_fd(int n, int fd);
int	ft_putunbr_fd(unsigned int n, int fd);
int	ft_puthex_fd(long long int n, int fd);
int	ft_puthex_up_fd(long long int n, int fd);
int ft_putptr_fd(long long int n, int fd);
int	ft_putnbr_base_fd(long long int n, char *base, int fd);
int	ft_putstr_fd(char *s, int fd);
int	ft_putchar_fd(char c, int fd);

#endif