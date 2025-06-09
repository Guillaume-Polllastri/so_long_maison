# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gpollast <gpollast@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/30 10:11:30 by gpollast          #+#    #+#              #
#    Updated: 2025/06/09 09:44:47 by gpollast         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = so_long

SRC = main.c get_next_line.c get_next_line_utils.c
OBJ = $(SRC:.c=.o)

CFLAGS = -Wall -Werror -Wextra -I./minilibx-linux
LDFLAGS = -L./MLX42/build -lmlx42 -lglfw -ldl -lm

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(OBJ) $(CFLAGS) $(LDFLAGS) -o $(NAME)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all