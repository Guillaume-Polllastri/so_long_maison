# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gpollast <gpollast@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/30 10:11:30 by gpollast          #+#    #+#              #
#    Updated: 2025/05/30 10:11:53 by gpollast         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = so_long

# Source files
SRCS = src/main.c
OBJS = $(SRCS:.c=.o)

# MLX42 paths
MLX_DIR = MLX42
MLX_BUILD = $(MLX_DIR)/build
MLX_INC = -I$(MLX_DIR)/include
MLX_LIB = -L$(MLX_BUILD) -lmlx42

# Compiler flags
CFLAGS = -Wall -Wextra -Werror $(MLX_INC)
LDFLAGS = $(MLX_LIB) -ldl -lglfw -lm -pthread

# Compile your binary
all: $(NAME)

$(NAME): $(OBJS)
	@make -C $(MLX_DIR)/build # build MLX42 if not done
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LDFLAGS)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all