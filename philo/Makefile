# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mspasic <mspasic@student.hive.fi>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/30 16:34:03 by mspasic           #+#    #+#              #
#    Updated: 2024/09/03 09:27:14 by mspasic          ###   ########.fr        #
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
		utils.c \
		utils2.c

OBJECTS = $(SOURCES:.c=.o)

CC = cc 

FLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJECTS)
	$(CC) $(FLAGS) $(OBJECTS) -o $(NAME) -I include/

%.o: %.c
	$(CC) $(FLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
