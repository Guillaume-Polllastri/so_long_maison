/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpollast <gpollast@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 18:35:24 by gpollast          #+#    #+#             */
/*   Updated: 2025/06/09 19:22:40 by gpollast         ###   ########.fr       */
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

static void	draw_entity(t_game *game, t_img *img, int x, int y)
{
	while (y < game->win_size.height / game->map->heigth)
	{
		x = 0;
		while (x < game->win_size.width / game->map->width)
		{
			
		}
	}
	game->map->data[y][x]
}

void	draw_frame(t_game *game)
{
	// t_img	img;

	// img.img = mlx_new_image(game->mlx, game->win_size.width, game->win_size.height);
	// img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
	// 		&img.endian);
	// my_mlx_pixel_put(&img, 5, 5, 0xFFFFFFFF);
	// mlx_put_image_to_window(game->mlx, game->mlx_win, img.img, 0, 0);
}
