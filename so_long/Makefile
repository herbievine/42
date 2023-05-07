# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: herbie <herbie@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/11 21:43:09 by herbie            #+#    #+#              #
#    Updated: 2023/05/07 15:00:42 by herbie           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = so_long

CC = gcc
CFLAGS = -Wall -Wextra -Werror -I/opt/X11/include

RM = rm
RMFLAG = -f

MLX_DIR = ./mlx
MLX_LIB = $(MLX_DIR)/libmlx_$(UNAME).a
MLX_FLAGS = -Lmlx -lmlx -framework OpenGL -framework AppKit

X11_FLAGS = -L/usr/X11/lib -lXext -lX11

SRCS = \
	main.c \
	mem.c \
	str.c \
	split.c \
	free.c \
	display.c \
	print.c \
	parse.c \
	window.c \
	hooks.c \
	io.c \
	error.c 

OBJS = $(SRCS:.c=.o)

all: $(MLX_LIB) $(NAME)

.c.o:
	$(CC) $(CFLAGS) -Imlx -c -o $@ $<

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(MLX_FLAGS) $(X11_FLAGS) -o $(NAME) $(OBJS)

$(MLX_LIB):
	@make -C $(MLX_DIR)

clean:
	$(RM) $(RMFLAG) $(OBJS)

fclean: clean
	$(RM) $(RMFLAG) $(NAME)
	@make -C $(MLX_DIR) clean

re: fclean all

.PHONY: all clean run fclean re 