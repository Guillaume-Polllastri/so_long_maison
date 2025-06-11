/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpollast <gpollast@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 16:38:42 by gpollast          #+#    #+#             */
/*   Updated: 2025/06/11 18:13:53 by gpollast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include "mlx.h"

int	game_open_window(t_game *game, int width, int height)
{
	game->win_size.width = width;
	game->win_size.height = height;
	game->img.img = mlx_new_image(game->mlx, game->win_size.width,
			game->win_size.height);
	game->img.addr = mlx_get_data_addr(game->img.img, &game->img.bits_per_pixel,
			&game->img.line_length, &game->img.endian);
	game->mlx_win = mlx_new_window(game->mlx, width, height, "so long.....");
	if (!game->mlx_win)
		return (0);
	if (!mlx_key_hook(game->mlx_win, ft_key_hook, game))
		return (0);
	mlx_loop_hook(game->mlx, draw_frame, game);
	return (1);
}

// void	game_destroy(t_game *game)
// {
// 	int	i;

// 	i = 0;
// 	while (game->map->data[i])
// 		i++;
// 	while (i >= 0)
// 		free(game->map->data[i--]);
// 	free(game->map->data);
// 	free(game->img);
// }

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
	mlx_loop(game->mlx);
	return (1);
}