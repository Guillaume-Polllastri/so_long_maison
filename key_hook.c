/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpollast <gpollast@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 12:50:03 by gpollast          #+#    #+#             */
/*   Updated: 2025/06/12 13:08:24 by gpollast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include "mlx.h"
#include <stdlib.h>
#include "ft_printf.h"

static void	key_move(int keycode, t_game *game, int row, int col)
{
	if (keycode == W || keycode == UP_ARROW)
	{
		if (game->map->data[row - 1][col] != WALL)
			game->map->player.y -= 1;
	}
	if (keycode == A || keycode == LEFT_ARROW)
	{
		if (game->map->data[row][col - 1] != WALL)
			game->map->player.x -= 1;
	}
	if (keycode == S || keycode == DOWN_ARROW)
	{
		if (game->map->data[row + 1][col] != WALL)
			game->map->player.y += 1;
	}
	if (keycode == D || keycode == RIGHT_ARROW)
	{
		if (game->map->data[row][col + 1] != WALL)
			game->map->player.x += 1;
	}
}

int	ft_key_hook(int keycode, t_game *game)
{
	int			row;
	int			col;
	static int	count = 0;

	row = game->map->player.y;
	col = game->map->player.x;

	if (game->map->data[row][col] == COLLECTIBLE)
	{
		game->map->data[row][col] = PATH;
		count++;
	}
	if (game->map->data[row][col] == EXIT && count == game->map->nb_collect)
	{
		ft_printf("GG YOU WIN!!!!!!!!");
		mlx_destroy_window(game->mlx, game->mlx_win);
		exit(0);
	}
	if (keycode == ESC)
	{
		mlx_destroy_window(game->mlx, game->mlx_win);
		exit(0);
	}
	key_move(keycode, game, row, col);
	return (0);
}
