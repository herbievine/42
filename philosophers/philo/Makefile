# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: codespace <codespace@student.42.fr>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/11 21:43:09 by herbie            #+#    #+#              #
#    Updated: 2023/10/07 14:40:14 by codespace        ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

CC = clang
CFLAGS = -Wall -Wextra -Werror #-fsanitize=thread

RM = rm
RMFLAG = -f

ifeq ($(shell uname), Linux)
	PTHREAD_FLAGS = -pthread
endif

SRCS = \
	main.c \
	int.c \
	error.c \
	parse.c \
	threads.c \
	time.c \
	exit.c \
	actions.c \
	structs.c

OBJS = $(SRCS:.c=.o)

all: $(NAME)

bonus: all

.c.o:
	$(CC) $(CFLAGS) -c -o $@ $<

$(NAME): $(OBJS) 
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(PTHREAD_FLAGS)

clean:
	$(RM) $(RMFLAG) $(OBJS)

fclean: clean
	$(RM) $(RMFLAG) $(NAME)

re: fclean all

.PHONY: all clean run fclean re 
