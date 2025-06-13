/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpollast <gpollast@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 10:07:18 by gpollast          #+#    #+#             */
/*   Updated: 2025/06/13 16:05:59 by gpollast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H	
# define SO_LONG_H

# include <stddef.h>

# define ESC 65307
# define W 119
# define A 97
# define S 115
# define D 100
# define UP_ARROW 65362
# define LEFT_ARROW 65361
# define RIGHT_ARROW 65363
# define DOWN_ARROW 65364

typedef enum e_elem
{
	WALL,
	PATH,
	MONSTER,
	PLAYER,
	COLLECTIBLE,
	EXIT
}	t_elem;

typedef struct s_point
{
	int	x;
	int	y;
}	t_point;

typedef struct s_map
{
	size_t		width;
	size_t		heigth;
	t_elem		**data;
	t_point		player;
	t_point		end;
	int			nb_collect;
	int			nb_player;
	int			nb_exit;
}	t_map;

typedef struct s_size
{
	int	width;
	int	height;
}	t_size;

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_img;

typedef struct s_game
{
	void	*mlx_win;
	void	*mlx;
	t_map	*map;
	t_size	win_size;
	t_img	img;
}	t_game;

int		parse_map(t_map *map, char *path);
void	*ft_realloc(void *ptr, size_t old_elm, size_t new_elm, size_t size_elm);
int		print_map(t_map *map);
int		game_loop(t_game *game);
int		game_init(t_game *game, t_map *map);
int		game_open_window(t_game *game, int width, int height);
int		draw_frame(t_game *game);
int		ft_key_hook(int keycode, t_game *game);
void	draw_player(t_game *game);
void	game_destroy(t_game *game);
int 	check_map_is_rectangle(t_map *map);

#endif