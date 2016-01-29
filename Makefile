# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fkalb <fkalb@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/03/07 14:03:10 by fkalb             #+#    #+#              #
#    Updated: 2015/03/07 19:08:21 by fkalb            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC=gcc
NAME=fdf
FLAGS= -W -Wall -Wextra -Werror -lmlx -lXext -lX11 -lft -O2

INC_DIR=./inc/

SRCS=$(addprefix ./src/, $(addsuffix .c, $(SRC_LIST)))
SRC_LIST=main\
		 move\
		 draw\
		 map

.SILENT: all $(NAME) clean fclean re
.PHONY: all $(NAME) clean fclean re

all : $(NAME)

$(NAME):
	echo "[ \033[0;33;mcompiling\033[0m ]"
	make -C ./libft
	$(CC) $(FLAGS) $(SRCS) -I$(INC_DIR) -I./libft/includes -L./libft/ -L/usr/X11/lib/ -o $(NAME)
	echo "[ \033[0;32;msuccessfuly\033[0m ]" $(NAME) "was created"

clean:
	echo "[ \033[0;33;mcleaning\033[0m ]"
	make -C ./libft clean

fclean: clean
	rm -f $(NAME)
	make -C ./libft fclean
	echo "[ \033[0;31;mdel\033[0m ]"$(NAME)

re: fclean all
