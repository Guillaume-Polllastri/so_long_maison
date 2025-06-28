/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpollast <gpollast@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 16:38:42 by gpollast          #+#    #+#             */
/*   Updated: 2025/06/28 22:24:53 by gpollast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include "mlx.h"
#include "ft_printf.h"
#include <stdlib.h>
#include "libft.h"

static int	game_do_loop(t_game *game)
{
	int	row;
	int	col;
	int	count;

	row = game->map->player.coord.y;
	col = game->map->player.coord.x;
	count = game->map->count_collect;
	if (game->map->data[row][col] == EXIT && count == game->map->nb_collect)
	{
		ft_printf("GG YOU WIN THIS GAME IN %d STEPS !!!\n",
			game->map->player.step);
		close_window(game);
		return (0);
	}
	draw_frame(game);
	return (1);
}

int	game_open_window(t_game *game, int width, int height)
{
	int	len_y;
	int	len_x;

	game->win_size.width = width;
	game->win_size.height = height;
	len_y = game->win_size.height / game->map->heigth;
	len_x = game->win_size.width / game->map->width;
	if (len_x < len_y)
		len_y = len_x;
	else if (len_y < len_x)
		len_x = len_y;
	game->box_size = len_x;
	game->img.img = mlx_new_image(game->mlx, game->win_size.width,
			game->win_size.height);
	game->img.addr = mlx_get_data_addr(game->img.img, &game->img.bits_per_pixel,
			&game->img.line_length, &game->img.endian);
	game->mlx_win = mlx_new_window(game->mlx, width, height, "The Ermango");
	if (!game->mlx_win)
		return (0);
	if (!mlx_key_hook(game->mlx_win, ft_key_hook, game))
		return (0);
	mlx_hook(game->mlx_win, 17, 0, close_window, game);
	mlx_loop_hook(game->mlx, game_do_loop, game);
	return (1);
}

int	game_init(t_game *game, t_map *map)
{
	ft_bzero(game, sizeof(t_game));
	game->mlx = mlx_init();
	game->map = map;
	game->map->count_collect = 0;
	game->map->player.step = 0;
	if (!sprite_init(game, "sprites/arbres.xpm", SPRITE_TREE))
		return (0);
	if (!sprite_init(game, "sprites/chemin.xpm", SPRITE_PATH))
		return (0);
	if (!sprite_init(game, "sprites/ermango.xpm", SPRITE_ERMANGO))
		return (0);
	if (!sprite_init(game, "sprites/hole.xpm", SPRITE_HOLE))
		return (0);
	if (!sprite_init(game, "sprites/mango.xpm", SPRITE_MANGO))
		return (0);
	if (!game->mlx || !game->map)
		return (0);
	return (1);
}

void	game_destroy(t_game *game)
{
	int	i;

	map_destroy(game->map);
	mlx_destroy_image(game->mlx, game->img.img);
	i = 0;
	while (i < SPRITE_COUNT)
	{
		mlx_destroy_image(game->mlx, game->sprites[i].asset.img);
		i++;
	}
	mlx_destroy_display(game->mlx);
	free(game->mlx);
}

int	game_loop(t_game *game)
{
	mlx_loop(game->mlx);
	mlx_destroy_window(game->mlx, game->mlx_win);
	return (1);
}
