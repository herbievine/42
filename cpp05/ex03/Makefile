# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: codespace <codespace@student.42.fr>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/11 09:59:04 by herbie            #+#    #+#              #
#    Updated: 2024/04/22 10:05:13 by codespace        ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = intern

CC = c++
CFLAGS = -Wall -Wextra -Werror -std=c++98

RM = rm
RMFLAG = -f

SRCS = \
	main.cpp \
	Bureaucrat.cpp \
	Intern.cpp \
	AForm.cpp \
	RobotomyRequestForm.cpp \
	ShrubberyCreationForm.cpp \
	PresidentialPardonForm.cpp

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
