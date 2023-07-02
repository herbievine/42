# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: herbie <herbie@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/11 21:43:09 by herbie            #+#    #+#              #
#    Updated: 2023/07/02 16:26:54 by herbie           ###   ########.fr        #
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
	io.c \
	print.c \
	display.c \

OBJS = $(SRCS:.c=.o)

all: $(NAME)

bonus: all

.c.o: # compile + link to readline
	$(CC) $(CFLAGS) -c $< -o $(<:.c=.o)
	

$(NAME): $(OBJS) 
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

clean:
	$(RM) $(RMFLAG) $(OBJS)

fclean: clean
	$(RM) $(RMFLAG) $(NAME)

re: fclean all

.PHONY: all clean run fclean re 
