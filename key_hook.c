/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpollast <gpollast@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 12:50:03 by gpollast          #+#    #+#             */
/*   Updated: 2025/06/24 19:06:12 by gpollast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include "mlx.h"
#include <stdlib.h>
#include "ft_printf.h"
#include "libft.h"

static void	move(t_game *game)
{

}

static void	key_move(int keycode, t_game *game, int row, int col)
{
	if (keycode == W || keycode == UP_ARROW)
	{
		if (game->map->data[row - 1][col] != WALL)
		{
			game->map->player.coord.y -= 1;
			game->map->player.step++;
		}
	}
	if (keycode == A || keycode == LEFT_ARROW)
	{
		if (game->map->data[row][col - 1] != WALL)
		{
			game->map->player.coord.x -= 1;
			game->map->player.step++;
		}
	}
	if (keycode == S || keycode == DOWN_ARROW)
	{
		if (game->map->data[row + 1][col] != WALL)
		{
			game->map->player.coord.y += 1;
			game->map->player.step++;
		}
	}
	if (keycode == D || keycode == RIGHT_ARROW)
	{
		if (game->map->data[row][col + 1] != WALL)
		{
			game->map->player.coord.x += 1;
			game->map->player.step++;
		}
	}
}

static void	step_count(t_game *game, int tmp)
{
	if (tmp != game->map->player.step)
	{
		tmp = game->map->player.step;
	}
}

int	close_window(t_game *game)
{
	mlx_destroy_window(game->mlx, game->mlx_win);
	exit(0);
	return (0);
}

int	ft_key_hook(int keycode, t_game *game)
{
	int			row;
	int			col;
	int			tmp;

	row = game->map->player.coord.y;
	col = game->map->player.coord.x;
	tmp = game->map->player.step;
	if (game->map->data[row][col] == COLLECTIBLE)
	{
		game->map->data[row][col] = PATH;
		game->map->count_collect++;
	}
	if (keycode == ESC)
	{
		mlx_destroy_window(game->mlx, game->mlx_win);
		exit(0);
	}
	key_move(keycode, game, row, col);
	step_count(game, tmp);
	return (0);
}
