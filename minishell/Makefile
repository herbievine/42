# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jcros <jcros@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/11 21:43:09 by herbie            #+#    #+#              #
#    Updated: 2023/12/06 20:37:22 by jcros            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = cc
CFLAGS = -Wall -Wextra -Werror


RM = rm
RMFLAG = -f

SRCS = \
	main.c \
	mem.c \
	str.c \
	char.c \
	print.c \
	display.c \
	parse.c \
	parse_utils.c \
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
	free.c \
	here_doc.c \
	process.c \
	builtin.c \
	env.c \
	expand.c \
	expand_utils.c \
	env2.c \
	exit.c \
	quotes.c \
	process_utils.c \
	process_utils2.c \
	str_c.c \
	builtins/cd.c \
	builtins/exit.c \
	builtins/export.c \
	builtins/echo.c \
	builtins/env.c \
	builtins/pwd.c \
	builtins/unset.c \
	
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
