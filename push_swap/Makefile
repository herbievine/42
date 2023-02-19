# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hvine <hvine@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/11 21:43:09 by herbie            #+#    #+#              #
#    Updated: 2023/02/19 11:16:58 by hvine            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = push_swap

CC = cc
CFLAGS = -Wall -Wextra -Werror

RM = rm
RMFLAG = -f

SRCS = \
	main.c \
	lib.c \
	num.c \
	strings.c \
	ops.c \
	display.c \
	lists.c \
	math.c

INCLUDES = \
	./lib.h \
	./num.h \
	./strings.h \
	./ops.h \
	./display.h \
	./lists.h \
	./math.h

OBJS = $(SRCS:.c=.o)

# Some shit from SO. `make run [...args]` will run the program with args
# Won't work for negatif numbers though...
ifeq (run,$(firstword $(MAKECMDGOALS)))
  RUN_ARGS := $(wordlist 2,$(words $(MAKECMDGOALS)),$(MAKECMDGOALS))
  $(eval $(RUN_ARGS):;@:)
endif

all: $(NAME) compile

$(NAME): $(OBJS) $(INCLUDES)
	$(CC) $(CFLAGS) -o $< -c $(<:.o=.c)

$(PACKAGES):
	$(MAKE) -C $(addprefix $(PACKAGES_PATH)/, $@)

clean:
	$(RM) $(RMFLAG) $(OBJS)

compile:
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

run: all
	./$(NAME) $(RUN_ARGS)

fclean: clean
	$(RM) $(RMFLAG) $(NAME)

re: fclean all

.PHONY: all clean run fclean re 