# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: herbie <herbie@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/22 11:57:59 by herbie            #+#    #+#              #
#    Updated: 2022/11/12 15:40:45 by hvine            ###   ########.fr        #
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
	./ft_strlen.c \
	./ft_strlcpy.c \
	./ft_strlcat.c \
	./ft_strchr.c \
	./ft_strrchr.c \
	./ft_strncmp.c \
	./ft_strnstr.c \
	./ft_strdup.c \
	./ft_isdigit.c \
	./ft_atoi.c \
	./ft_isalpha.c \
	./ft_isalnum.c \
	./ft_isascii.c \
	./ft_isprint.c \
	./ft_toupper.c \
	./ft_tolower.c \
	./ft_substr.c \
	./ft_strjoin.c \
	./ft_strtrim.c \
	./ft_split.c \
	./ft_itoa.c \
	./ft_strmapi.c \
	./ft_striteri.c \
	./ft_putchar_fd.c \
	./ft_putstr_fd.c \
	./ft_putendl_fd.c \
	./ft_putnbr_fd.c

BONUS_SRCS = \
	./ft_lstnew_bonus.c \
	./ft_lstadd_front_bonus.c \
	./ft_lstsize_bonus.c \
	./ft_lstlast_bonus.c \
	./ft_lstadd_back_bonus.c \
	./ft_lstdelone_bonus.c \
	./ft_lstclear_bonus.c \
	./ft_lstiter_bonus.c \
	./ft_lstmap_bonus.c

#EXTRA_SRCS = \
#	./ft_test_malloc.c
	
OBJS = $(SRCS:.c=.o) #$(EXTRA_SRCS:.c=.o)
BONUS_OBJS = $(BONUS_SRCS:.c=.o)

all: $(NAME)

bonus: $(BONUS_OBJS) $(NAME)
	$(AR) $(ARFLAGS) $(NAME) $(BONUS_OBJS)

.c.o: $(SRCS) $(INCLUDES)
	$(CC) $(CFLAGS) -c $< -o $(<:.c=.o)

clean:
	$(RM) $(RMFLAG) $(OBJS) $(BONUS_OBJS)

fclean: clean
	$(RM) $(RMFLAG) $(NAME)

re: fclean all

$(NAME): $(OBJS)
	$(AR) $(ARFLAGS) $@ $^

so:
	$(CC) -nostartfiles -fPIC $(CFLAGS) $(SRCS) $(BONUS_SRCS)
	gcc -nostartfiles -shared -o libft.so $(OBJS) $(BONUS_OBJS)

.PHONY: all clean fclean re
