# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: herbie <herbie@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/10/23 11:59:38 by herbie            #+#    #+#              #
#    Updated: 2026/10/23 11:59:38 by herbie           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = graph

CC = c++
CFLAGS = -Wall -Wextra -Werror -std=c++98

RM = rm
RMFLAG = -f

SRCS = main.cpp Vector2.cpp Graph.cpp

OBJS = $(SRCS:.cpp=.o)

all: $(NAME)

bonus: all

.cpp.o:
	$(CC) $(CFLAGS) -c $< -o $(<:.cpp=.o)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

clean:
	$(RM) $(RMFLAG) $(OBJS)

fclean: clean
	$(RM) $(RMFLAG) $(NAME)

re: fclean all

.PHONY: all clean run fclean re
