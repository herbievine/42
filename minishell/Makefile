# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: herbie <herbie@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/11 21:43:09 by herbie            #+#    #+#              #
#    Updated: 2023/12/03 11:22:43 by herbie           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = cc
CFLAGS = -g -Wall -Wextra -Werror

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
	lists.c \
	here_doc.c \
	get_line.c \
	process.c \
	builtin.c \
	env.c \
	expand.c \
	expand_utils.c \
	env2.c \
	exit.c \
	quotes.c \
	process_utils.c \
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
