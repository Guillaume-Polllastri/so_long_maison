/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpollast <gpollast@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 16:38:42 by gpollast          #+#    #+#             */
/*   Updated: 2025/06/10 12:51:43 by gpollast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include "mlx.h"

int	game_open_window(t_game *game, int width, int height)
{
	game->win_size.width = width;
	game->win_size.height = height;
	game->mlx_win = mlx_new_window(game->mlx, width, height, "so long.....");
	if (!game->mlx_win)
		return (0);
	return (1);
}

int	game_init(t_game *game, t_map *map)
{
	game->mlx = mlx_init();
	game->map = map;
	if (!game->mlx || !game->map)
		return (0);
	return (1);
}

int	game_loop(t_game *game)
{
	draw_frame(game);
	mlx_key_hook(game->mlx_win, close, game);
	mlx_loop(game->mlx);
	return (1);
}