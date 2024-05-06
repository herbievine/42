# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: herbie <herbie@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/11 09:59:04 by herbie            #+#    #+#              #
#    Updated: 2024/05/06 13:54:47 by herbie           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = array

CC = c++
CFLAGS = -Wall -Wextra -Werror -std=c++98

RM = rm
RMFLAG = -f

SRCS = main.cpp

OBJS = $(SRCS:.cpp=.o)

all: $(NAME)

bonus: all

.c.o:
	$(CC) $(CFLAGS) -c $< -o $(<:.cpp=.o)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

clean:
	$(RM) $(RMFLAG) $(OBJS)

fclean: clean
	$(RM) $(RMFLAG) $(NAME)

re: fclean all

.PHONY: all clean run fclean re
