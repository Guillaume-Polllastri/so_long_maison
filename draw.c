/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpollast <gpollast@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 18:35:24 by gpollast          #+#    #+#             */
/*   Updated: 2025/06/10 11:26:50 by gpollast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include "mlx.h"

static void	my_mlx_pixel_put(t_img *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

static void	draw_color(t_game *game, t_img img, t_point point, t_point pixel)
{
	if (game->map->data[point.y][point.x] == WALL)
		my_mlx_pixel_put(&img, pixel.x, pixel.y, 0x851c1c);
	else if (game->map->data[point.y][point.x] == PATH)
		my_mlx_pixel_put(&img, pixel.x, pixel.y, 0xFFFFFFFF);
	else if (game->map->data[point.y][point.x] == PLAYER)
		my_mlx_pixel_put(&img, pixel.x, pixel.y, 0x070ea3);
	else if (game->map->data[point.y][point.x] == COLLECTIBLE)
		my_mlx_pixel_put(&img, pixel.x, pixel.y, 0xd9c407);
	else if (game->map->data[point.y][point.x] == EXIT)
		my_mlx_pixel_put(&img, pixel.x, pixel.y, 0xde0bbb);
}

static void	draw_entity(t_game *game, t_img img, t_point point)
{
	t_point	pixel;
	size_t	len_y;
	size_t	len_x;

	pixel.x = 0;
	pixel.y = 0;
	len_y = game->win_size.height / game->map->heigth;
	len_x = game->win_size.width / game->map->width;
	pixel.y = point.y * len_y;
	while (pixel.y < ((point.y + 1) * len_y))
	{
		pixel.x = point.x * (game->win_size.width / game->map->width);
		while (pixel.x < ((point.x + 1) * len_x))
		{
			draw_color(game, img, point, pixel);
			pixel.x++;
		}
		pixel.y++;
	}
}

void	draw_frame(t_game *game)
{
	t_img	img;
	t_point	point;

	img.img = mlx_new_image(game->mlx, game->win_size.width,
			game->win_size.height);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
			&img.endian);
	point.x = 0;
	point.y = 0;
	while ((size_t) point.y < game->map->heigth)
	{
		point.x = 0;
		while ((size_t) point.x < game->map->width)
		{
			draw_entity(game, img, point);
			point.x++;
		}
		point.y++;
	}
	mlx_put_image_to_window(game->mlx, game->mlx_win, img.img, 0, 0);
}
