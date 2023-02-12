# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: herbie <herbie@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/11 21:43:09 by herbie            #+#    #+#              #
#    Updated: 2023/02/11 18:24:42 by herbie           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a

AR = ar
ARFLAGS = crs

CC = cc
CFLAGS = -Wall -Wextra -Werror

RM = rm
RMFLAG = -f

INCLUDES = ./ft_printf.h

SRCS = \
	./ft_printf.c \
	./ft_putchar_fd.c \
	./ft_putnbr_fd.c \
	./ft_putunbr_fd.c \
	./ft_puthex_fd.c \
	./ft_puthex_up_fd.c \
	./ft_putptr_fd.c \
	./ft_putstr_fd.c \
	./ft_putnbr_base_fd.c \
	./ft_strchr.c \
	./ft_strlen.c \
	./ft_intlen.c
	
OBJS = $(SRCS:.c=.o)

all: $(NAME)

.c.o: $(SRCS) $(INCLUDES)
	$(CC) $(CFLAGS) -c $< -o $(<:.c=.o)

clean:
	$(RM) $(RMFLAG) $(OBJS)

fclean: clean
	$(RM) $(RMFLAG) $(NAME)

re: fclean all

$(NAME): $(OBJS) 
	$(AR) $(ARFLAGS) $@ $^

.PHONY: all clean fclean re