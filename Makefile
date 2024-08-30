# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mspasic <mspasic@student.hive.fi>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/30 16:34:03 by mspasic           #+#    #+#              #
#    Updated: 2024/08/30 15:07:13 by mspasic          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

SOURCES = main.c \
		checks.c \
		handle_args.c \
		ft_atoi.c \
		life.c \
		monitoring.c \
		timing.c \
		utils.c

OBJECTS = $(SOURCES:.c=.o)

CC = gcc

FLAGS = -Wall -Wextra -Werror -g -fsanitize=address  

all: $(NAME)

$(NAME): $(OBJECTS)
	$(CC) $(FLAGS) -o $(NAME) $(OBJECTS) -I include

clean:
	rm -f $(OBJECTS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
