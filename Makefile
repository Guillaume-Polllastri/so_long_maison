# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gpollast <gpollast@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/30 10:11:30 by gpollast          #+#    #+#              #
#    Updated: 2025/06/28 19:54:15 by gpollast         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = so_long

SRC = 	main.c \
		get_next_line.c \
		get_next_line_utils.c \
		parse_map.c \
		utils.c \
		game.c \
		draw.c \
		key_hook.c \
		parse_map_utils.c \
		sprite.c \
		map.c

OBJ = $(SRC:.c=.o)

CC = gcc
CFLAGS = -Wall -Werror -Wextra -I./minilibx-linux -I./includes -I./libft -g
LDFLAGS = -L./minilibx-linux -lmlx -L./libft -lft -L. -lftprintf -lX11 -lXext -lm

all: libft/libft.a minilibx $(NAME)

libft/libft.a:
	@$(MAKE) -C libft

minilibx:
	@$(MAKE) -C minilibx-linux

$(NAME): $(OBJ)
	@$(CC) $(OBJ) $(CFLAGS) $(LDFLAGS) -o $(NAME)

clean:
	@rm -f $(OBJ)
	@$(MAKE) -C libft clean
	@echo "Suppression des fichiers objets (project + libft)"

fclean: clean
	@rm -f $(NAME)
	@$(MAKE) -C libft fclean
	@echo "Suppression de l'exécutable et de la librairie"

re: fclean all