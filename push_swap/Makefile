# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: herbie <herbie@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/11 21:43:09 by herbie            #+#    #+#              #
#    Updated: 2023/02/16 09:43:06 by herbie           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = push_swap

CC = cc
CFLAGS = -Wall -Wextra -Werror

RM = rm
RMFLAG = -f

SRCS = main.c

INCLUDES = \
	./packages/packages.h

PACKAGES_PATH = ./packages
PACKAGES = \
	libft


OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS) $(PACKAGES)
	$(CC) $(CFLAGS) -I $(INCLUDES) -o $< -c $(<:.o=.c) -I$(addsuffix .a, $(addsuffix $(word 2,$^), $(addprefix $(PACKAGES_PATH)/, $(word 2,$^)/)))

$(PACKAGES):
	$(MAKE) -C $(addprefix $(PACKAGES_PATH)/, $@)

clean:
	$(RM) $(RMFLAG) $(OBJS)

# clean:
# 	$(MAKE) -C $@ clean

fclean: clean
	$(RM) $(RMFLAG) $(NAME)

re: fclean all

.PHONY: all clean fclean re