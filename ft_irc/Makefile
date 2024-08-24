# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: herbie <herbie@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/11 09:59:04 by herbie            #+#    #+#              #
#    Updated: 2024/08/24 09:33:12 by herbie           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ircserv

CC = c++
CFLAGS = -Wall -Wextra -Werror -std=c++98

RM = rm
RMFLAG = -f

SRCS = \
	src/main.cpp \
	src/client/Client.cpp \
	src/server/Server.cpp \
	src/channel/Channel.cpp \
	src/commands/cap.cpp \
	src/commands/join.cpp \
	src/commands/nick.cpp \
	src/commands/part.cpp \
	src/commands/pass.cpp \
	src/commands/ping.cpp \
	src/commands/pong.cpp \
	src/commands/quit.cpp \
	src/commands/user.cpp \
	src/utils/detect.cpp \
	src/utils/split.cpp \
	src/utils/trim.cpp

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
