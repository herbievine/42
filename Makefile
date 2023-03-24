# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: herbie <herbie@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/23 21:40:43 by herbie            #+#    #+#              #
#    Updated: 2023/03/24 14:15:51 by herbie           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

PROJECT = libft \
	ft_printf \
	push_swap \
	pipex

all: 
	@for i in $(PROJECT); do \
		make -C $$i; \
	done

fclean:
	@for i in $(PROJECT); do \
		make -C $$i fclean; \
	done

re: fclean all

.PHONY: all fclean
