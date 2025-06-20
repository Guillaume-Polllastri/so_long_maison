/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpollast <gpollast@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 16:38:42 by gpollast          #+#    #+#             */
/*   Updated: 2025/06/20 16:07:52 by gpollast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include "mlx.h"
#include "ft_printf.h"

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
		ft_printf("GG YOU WIN!!!!!!!!");
		mlx_destroy_window(game->mlx, game->mlx_win);
		return (0);
	}
	draw_frame(game);
	return (1);
}

int	game_open_window(t_game *game, int width, int height)
{
	game->win_size.width = width;
	game->win_size.height = height;
	sprite_init(game);
	game->img.img = mlx_new_image(game->mlx, game->win_size.width,
			game->win_size.height);
	game->img.addr = mlx_get_data_addr(game->img.img, &game->img.bits_per_pixel,
			&game->img.line_length, &game->img.endian);
	game->mlx_win = mlx_new_window(game->mlx, width, height, "so long.....");
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
	game->mlx = mlx_init();
	game->map = map;
	game->map->count_collect = 0;
	game->map->player.step = 0;
	if (!game->mlx || !game->map)
		return (0);
	return (1);
}

int	game_loop(t_game *game)
{
	mlx_loop(game->mlx);
	return (1);
}
