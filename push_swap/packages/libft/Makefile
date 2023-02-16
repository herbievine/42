# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: herbie <herbie@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/22 11:57:59 by herbie            #+#    #+#              #
#    Updated: 2023/02/16 09:55:22 by herbie           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

AR = ar
ARFLAGS = crs

CC = cc
CFLAGS = -Wall -Wextra -Werror

RM = rm
RMFLAG = -f

INCLUDES = ./libft.h

SRCS = \
	./ft_memset.c \
	./ft_bzero.c \
	./ft_memcpy.c \
	./ft_memmove.c \
	./ft_memchr.c \
	./ft_memcmp.c \
	./ft_calloc.c \
	./ft_atoi.c \
	./ft_itoa.c \
	./ft_strjoin.c \
	./ft_split.c \
	./ft_strdup.c \
	./ft_strchr.c \
	./ft_strrchr.c \
	./ft_strnstr.c \
	./ft_substr.c \
	./ft_strtrim.c \
	./ft_strncmp.c \
	./ft_strlcpy.c \
	./ft_strlcat.c \
	./ft_strmapi.c \
	./ft_striteri.c \
	./ft_isalpha.c \
	./ft_isdigit.c \
	./ft_isalnum.c \
	./ft_isascii.c \
	./ft_isprint.c \
	./ft_tolower.c \
	./ft_toupper.c \
	./ft_printf.c \
	./ft_putchar_fd.c \
	./ft_putstr_fd.c \
	./ft_putendl_fd.c \
	./ft_putnbr_fd.c \
	./ft_putunbr_fd.c \
	./ft_puthex_fd.c \
	./ft_puthex_up_fd.c \
	./ft_putptr_fd.c \
	./ft_putnbr_base_fd.c \
	./ft_putchar_fd.c \
	./ft_putstr_fd.c \
	./ft_putendl_fd.c \
	./ft_putnbr_fd.c \
	./ft_putunbr_fd.c \
	./ft_puthex_fd.c \
	./ft_puthex_up_fd.c \
	./ft_putptr_fd.c \
	./ft_putnbr_base_fd.c \
	./ft_strlen.c \
	./ft_intlen.c 

OBJS = $(SRCS:.c=.o)

all: $(NAME)

bonus: $(NAME)
	$(AR) $(ARFLAGS) $(NAME)

.c.o: $(SRCS) $(INCLUDES)
	$(CC) $(CFLAGS) -c $< -o $(<:.c=.o)

clean:
	$(RM) $(RMFLAG) $(OBJS)

fclean: clean
	$(RM) $(RMFLAG) $(NAME)

re: fclean all

$(NAME): $(OBJS)
	$(AR) $(ARFLAGS) $@ $^

so:
	$(CC) -nostartfiles -fPIC $(CFLAGS) $(SRCS)
	gcc -nostartfiles -shared -o libft.so $(OBJS)

.PHONY: all clean fclean re
