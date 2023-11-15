# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: juliencros <juliencros@student.42.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/11 21:43:09 by herbie            #+#    #+#              #
#    Updated: 2023/11/15 15:34:15 by juliencros       ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = cc
CFLAGS = #-Wall -Wextra -Werror

RM = rm
RMFLAG = -f

SRCS = \
	main.c \
	mem.c \
	str.c \
	char.c \
	io.c \
	print.c \
	display.c \
	parse.c \
	error.c \
	lexer.c \
	lexer_utils.c \
	command.c \
	subcommand.c \
	history.c \
	signals.c \
	token.c \
	find_cmds.c \
	str2.c \
	str3.c \
	split.c \
	find_in_file.c \
	find_out_file.c \
	free.c \
	here_doc.c \
	get_line.c \
	check_subcommands.c \
	process.c \
	builtin.c \
	builtins_func.c \
	env.c \
	echo.c \
	echo_utils.c \
	expand.c \
	builtins_func_utils.c \
	env2.c \
	builtins_func2.c \
	exit.c \
	quotes.c \
	process_utils.c \

OBJS = $(SRCS:.c=.o)

all: $(NAME)

bonus: all

.c.o:
	$(CC) $(CFLAGS) -c $< -o $(<:.c=.o) $(shell pkg-config --cflags readline)

$(NAME): $(OBJS) 
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(shell pkg-config --libs readline)

clean:
	$(RM) $(RMFLAG) $(OBJS)

fclean: clean
	$(RM) $(RMFLAG) $(NAME)

re: fclean all

.PHONY: all clean run fclean re 
