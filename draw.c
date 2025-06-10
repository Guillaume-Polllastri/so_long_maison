/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpollast <gpollast@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 18:35:24 by gpollast          #+#    #+#             */
/*   Updated: 2025/06/10 11:01:40 by gpollast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include "mlx.h"

static void	my_mlx_pixel_put(t_img *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

static void	draw_color(t_game *game, t_img img, int x, int y, unsigned long y_pixel, unsigned long x_pixel)
{
	if (game->map->data[y][x] == WALL)
		my_mlx_pixel_put(&img, x_pixel, y_pixel, 0x851c1c);
	else if (game->map->data[y][x] == PATH)
		my_mlx_pixel_put(&img, x_pixel, y_pixel, 0xFFFFFFFF);
	else if (game->map->data[y][x] == PLAYER)
		my_mlx_pixel_put(&img, x_pixel, y_pixel, 0x070ea3);
	else if (game->map->data[y][x] == COLLECTIBLE)
		my_mlx_pixel_put(&img, x_pixel, y_pixel, 0xd9c407);
	else if (game->map->data[y][x] == EXIT)
		my_mlx_pixel_put(&img, x_pixel, y_pixel, 0xde0bbb);
}

static void	draw_entity(t_game *game, t_img img, int x, int y)
{
	unsigned long	y_pixel;
	unsigned long	x_pixel;

	y_pixel = y * (game->win_size.height / game->map->heigth);
	while (y_pixel < (y + 1) * (game->win_size.height / game->map->heigth))
	{
		x_pixel = x * (game->win_size.width / game->map->width);
		while (x_pixel < (x + 1) * (game->win_size.width / game->map->width))
		{
			draw_color(game, img, x, y, y_pixel, x_pixel);
			x_pixel++;
		}
		y_pixel++;
	}
}

void	draw_frame(t_game *game)
{
	t_img	img;
	size_t	x;
	size_t	y;

	img.img = mlx_new_image(game->mlx, game->win_size.width, game->win_size.height);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
			&img.endian);
	x = 0;
	y = 0;
	while (y < game->map->heigth)
	{
		x = 0;
		while (x < game->map->width)
		{
			draw_entity(game, img, x, y);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(game->mlx, game->mlx_win, img.img, 0, 0);
}
