# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: herbie <herbie@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/11 21:43:09 by herbie            #+#    #+#              #
#    Updated: 2023/02/11 20:38:05 by herbie           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

### ~~~ VARIABLES ~~~ ###

NAME = push_swap

CC = cc
CFLAGS = -Wall -Wextra -Werror

RM = rm
RMFLAG = -f

### ~~~ PATHS ~~~ ###

SRCS = \
	main.c

INCLUDES = \
	./packages/packages.h

### ~~~ PACKAGES ~~~ ###

PACKAGES_PATH = ./packages
PACKAGES = \
	ft_printf
	
### ~~~ OBJECTS ~~~ ###

OBJS = $(SRCS:.c=.o)

### ~~~ MAIN ~~~ ###

all: $(NAME)

### ~~~ BUILD RULES ~~~ ###

$(NAME): $(OBJS) $(PACKAGES)
	$(CC) $(CFLAGS) -I $(INCLUDES) -o $< -c $(<:.o=.c) -I$(addsuffix .a, $(addsuffix $(word 2,$^), $(addprefix $(PACKAGES_PATH)/, $(word 2,$^)/)))

$(PACKAGES):
	$(MAKE) -C $(addprefix $(PACKAGES_PATH)/, $@)

### ~~~ RULES ~~~ ###

clean:
	$(RM) $(RMFLAG) $(OBJS)

fclean: clean
	$(RM) $(RMFLAG) $(NAME)

re: fclean all

.PHONY: all clean fclean re