# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gpollast <gpollast@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/30 10:11:30 by gpollast          #+#    #+#              #
#    Updated: 2025/06/14 13:54:47 by gpollast         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = so_long

SRC = 	main.c \
		get_next_line.c \
		get_next_line_utils.c \
		parse_map.c \
		print_map.c \
		utils.c \
		game.c \
		draw.c \
		key_hook.c \
		parse_map_utils.c
OBJ = $(SRC:.c=.o)

CFLAGS = -Wall -Werror -Wextra -I./minilibx-linux -g
LDFLAGS = -L./minilibx-linux -lmlx -L. -lftprintf -lX11 -lXext -lm

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(OBJ) $(CFLAGS) $(LDFLAGS) -o $(NAME)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all