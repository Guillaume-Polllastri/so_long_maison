/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpollast <gpollast@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 10:07:18 by gpollast          #+#    #+#             */
/*   Updated: 2025/06/26 13:40:31 by gpollast         ###   ########.fr       */
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

# define SPRITE_TREE 0
# define SPRITE_PATH 1
# define SPRITE_ERMANGO 2
# define SPRITE_HOLE 3
# define SPRITE_MANGO 4

# define SPRITE_COUNT 5

typedef enum e_elem
{
	WALL,
	PATH,
	PLAYER,
	COLLECTIBLE,
	EXIT
}	t_elem;

typedef struct s_point
{
	int		x;
	int		y;
}	t_point;

typedef struct s_player
{
	t_point	coord;
	int		step;
}	t_player;

typedef struct s_map
{
	size_t		width;
	size_t		heigth;
	t_elem		**data;
	t_player	player;
	t_point		end;
	int			nb_collect;
	int			count_collect;
	int			nb_player;
	int			nb_exit;
	int			nb_test_collectible;
	int			nb_test_exit;
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
	t_size	size;
}				t_img;

typedef struct s_sprite
{
	int		*buffer;
	t_size	size;
	t_img	asset;
}	t_sprite;

typedef struct s_game
{
	void		*mlx_win;
	void		*mlx;
	t_map		*map;
	t_size		win_size;
	t_img		img;
	t_img		asset;
	t_sprite	sprites[5];
	int			box_size;
}	t_game;

int		parse_map(t_map *map, char *path);
void	*ft_realloc(void *ptr, size_t old_elm, size_t new_elm, size_t size_elm);
int		game_loop(t_game *game);
int		game_init(t_game *game, t_map *map);
int		game_open_window(t_game *game, int width, int height);
void	game_destroy(t_game *game);
int		draw_frame(t_game *game);
int		draw_background(t_game *game);
void	draw_player(t_game *game);
int		ft_key_hook(int keycode, t_game *game);
int		close_window(t_game *game);
int		flood_fill(t_map *map);
int		sprite_init(t_game *game, char *path, int id);
int		get_color_from_sprite(t_game *game, t_sprite *sprite,
			t_point *pixel);
void	draw_color(t_game *game, t_point *point, t_point *pixel);
void	set_pixel(t_img *data, int x, int y, int color);
int		check_file_extend(char *filename);
size_t	ft_strlen_no_nl(char *str);
void	map_destroy(t_map *map);
int		check_map(t_map *map);
#endif