# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: herbie <herbie@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/11 21:43:09 by herbie            #+#    #+#              #
#    Updated: 2023/04/27 11:56:42 by herbie           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = so_long

CC = gcc
CFLAGS = -Wall -Wextra -Werror

RM = rm
RMFLAG = -f

MLX_DIR = ./mlx
MLX_LIB = $(MLX_DIR)/libmlx_$(UNAME).a
MLX_FLAGS = -Lmlx -lmlx -framework OpenGL -framework AppKit

SRCS = \
	main.c \
	mem.c \
	str.c \
	split.c \
	free.c \
	display.c \
	print.c \

OBJS = $(SRCS:.c=.o)

all: $(MLX_LIB) $(NAME)

.c.o:
	$(CC) $(CFLAGS) -Imlx -c -o $@ $<

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(MLX_FLAGS) -o $(NAME) $(OBJS)

$(MLX_LIB):
	@make -C $(MLX_DIR)

clean:
	$(RM) $(RMFLAG) $(OBJS)

fclean: clean
	$(RM) $(RMFLAG) $(NAME)
	@make -C $(MLX_DIR) clean

re: fclean all

.PHONY: all clean run fclean re 