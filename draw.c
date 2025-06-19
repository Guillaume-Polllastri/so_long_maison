/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpollast <gpollast@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 18:35:24 by gpollast          #+#    #+#             */
/*   Updated: 2025/06/19 10:03:56 by gpollast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include "mlx.h"
#include <stdlib.h>
#include <stdio.h>

static void	my_mlx_pixel_put(t_img *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

static void	draw_color(t_game *game, t_point *point, t_point *pixel)
{
	if (game->map->data[point->y][point->x] == WALL)
		my_mlx_pixel_put(&game->img, pixel->x, pixel->y, 0x851c1c);
	else if (game->map->data[point->y][point->x] == PATH)
		my_mlx_pixel_put(&game->img, pixel->x, pixel->y, 0xFFFFFFFF);
	else if (game->map->data[point->y][point->x] == PLAYER)
		my_mlx_pixel_put(&game->img, pixel->x, pixel->y, 0x070ea3);
	else if (game->map->data[point->y][point->x] == COLLECTIBLE)
		my_mlx_pixel_put(&game->img, pixel->x, pixel->y, 0xd9c407);
	else if (game->map->data[point->y][point->x] == EXIT)
		my_mlx_pixel_put(&game->img, pixel->x, pixel->y, 0xde0bbb);
}

void	draw_player(t_game *game)
{
	t_point	pixel;
	size_t	len_y;
	size_t	len_x;
	size_t	toto;

	pixel.x = 0;
	pixel.y = 0;
	len_y = game->win_size.height / game->map->heigth;
	len_x = game->win_size.width / game->map->width;
	if (len_x < len_y)
		len_y = len_x;
	else if (len_y < len_x)
		len_x = len_y;
	toto = (game->win_size.height - (5 * len_y)) / 2;
	pixel.y = game->map->player.y * len_y + toto;
	while (pixel.y < (int)((game->map->player.y + 1) * len_y + toto))
	{
		pixel.x = game->map->player.x * (game->win_size.width / game->map->width);
		while (pixel.x < (int)((game->map->player.x + 1) * len_x))
		{
			my_mlx_pixel_put(&game->img, pixel.x, pixel.y, 0x070ea3);
			pixel.x++;
		}
		pixel.y++;
	}
}

static void	draw_entity(t_game *game, t_point *point)
{
	t_point	pixel;
	size_t	len_y;
	size_t	len_x;
	size_t	pos;

	len_y = game->win_size.height / game->map->heigth;
	len_x = game->win_size.width / game->map->width;
	if (len_x < len_y)
		len_y = len_x;
	else if (len_y < len_x)
		len_x = len_y;
	pos = (game->win_size.height - (5 * len_y)) / 2;
	pixel.y = point->y * len_y + pos;
	while (pixel.y < (int)((point->y + 1) * len_y + pos))
	{
		pixel.x = point->x * (game->win_size.width / game->map->width);
		while (pixel.x < (int)((point->x + 1) * len_x))
		{
			draw_color(game, point, &pixel);
			pixel.x++;
		}
		pixel.y++;
	}
}

int	draw_frame(t_game *game)
{
	t_point	point;

	draw_background(game);
	point.x = 0;
	point.y = 0;
	while ((size_t) point.y < game->map->heigth)
	{
		point.x = 0;
		while ((size_t) point.x < game->map->width)
		{
			draw_entity(game, &point);
			point.x++;
		}
		point.y++;
	}
	draw_player(game);
	mlx_put_image_to_window(game->mlx, game->mlx_win, game->img.img, 0, 0);
	return (0);
}
int	draw_background(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (y < game->win_size.height)
	{
		x = 0;
		while (x < game->win_size.width)
		{
			my_mlx_pixel_put(&game->img, x, y, 0x851c1c);
			x++;
		}
		y++;
	}
	return (1);
}