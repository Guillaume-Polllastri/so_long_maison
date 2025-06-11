/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpollast <gpollast@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 12:50:03 by gpollast          #+#    #+#             */
/*   Updated: 2025/06/11 18:22:43 by gpollast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include "mlx.h"
#include <stdlib.h>
#include <stdio.h>

int	ft_key_hook(int keycode, t_game *game)
{
	int	row;
	int	col;
	int	y_exit;
	int	x_exit;

	row = game->map->player.y;
	col = game->map->player.x;
	y_exit = game->map->end.y;
	x_exit = game->map->end.x;
	if (row == y_exit && col == x_exit)
	{
		mlx_destroy_window(game->mlx, game->mlx_win);
		exit(0);
	}
	if (keycode == ESC)
	{
		mlx_destroy_window(game->mlx, game->mlx_win);
		exit(0);
	}
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
	return (0);
}