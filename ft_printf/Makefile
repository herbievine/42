# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: codespace <codespace@student.42.fr>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/11 21:43:09 by herbie            #+#    #+#              #
#    Updated: 2022/11/16 10:34:41 by codespace        ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a

AR = ar
ARFLAGS = crs

CC = cc
# CFLAGS = -Wall -Wextra -Werror

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

# BONUS_SRCS = \
# 	./ft_lstnew_bonus.c \
# 	./ft_lstadd_front_bonus.c \
# 	./ft_lstsize_bonus.c \
# 	./ft_lstlast_bonus.c \
# 	./ft_lstadd_back_bonus.c \
# 	./ft_lstdelone_bonus.c \
# 	./ft_lstclear_bonus.c \
# 	./ft_lstiter_bonus.c \
# 	./ft_lstmap_bonus.c
	
OBJS = $(SRCS:.c=.o)
# BONUS_OBJS = $(BONUS_SRCS:.c=.o)

all: $(NAME)

# bonus: $(BONUS_OBJS) $(NAME)
# 	$(AR) $(ARFLAGS) $(NAME) $(BONUS_OBJS)

.c.o: $(SRCS) $(INCLUDES)
	$(CC) $(CFLAGS) -c $< -o $(<:.c=.o)

clean:
	$(RM) $(RMFLAG) $(OBJS) #$(BONUS_OBJS)

fclean: clean
	$(RM) $(RMFLAG) $(NAME)

re: fclean all

$(NAME): $(OBJS) 
	$(AR) $(ARFLAGS) $@ $^

.PHONY: all clean fclean re