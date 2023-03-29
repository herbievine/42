# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: herbie <herbie@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/11 21:43:09 by herbie            #+#    #+#              #
#    Updated: 2023/03/29 12:12:19 by herbie           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex

CC = cc
CFLAGS = #-Wall -Wextra -Werror

RM = rm
RMFLAG = -f

SRCS = \
	main.c \
	get_next_line.c \
	mem.c \
	str.c \
	io.c \
	parse.c \
	split.c \
	error.c

# INCLUDES = \
# 	./lib.h \
# 	./strings.h \
# 	./ops.h \
# 	./display.h \
# 	./lists.h \
# 	./arrays.h \
# 	./parse.h \
# 	./utils.h \
# 	./split.h

OBJS = $(SRCS:.c=.o)

all: $(NAME)

.c.o:
	$(CC) $(CFLAGS) -c $< -o $(<:.c=.o)

$(NAME): $(OBJS) # $(INCLUDES)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

clean:
	$(RM) $(RMFLAG) $(OBJS)

# compile: $(NAME)
# 	$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

fclean: clean
	$(RM) $(RMFLAG) $(NAME)

re: fclean all

.PHONY: all clean run fclean re 