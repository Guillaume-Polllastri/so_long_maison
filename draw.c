/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpollast <gpollast@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 18:35:24 by gpollast          #+#    #+#             */
/*   Updated: 2025/06/23 15:18:25 by gpollast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include "mlx.h"
#include <stdlib.h>
#include <stdio.h>
#include "libft.h"

void	my_mlx_pixel_put(t_img *data, int x, int y, int color)
{
	char	*dst;

	if (!(color & 0xFF))
		return ;
	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	draw_player(t_game *game)
{
	t_point	pixel;
	size_t	toto;

	pixel.x = 0;
	pixel.y = 0;
	// toto = (game->win_size.height - (game->map->heigth * len_y)) / 2;
	toto = 0;
	pixel.y = game->map->player.coord.y * game->box_size + toto;
	while (pixel.y < (int)((game->map->player.coord.y + 1)
		* game->box_size + toto))
	{
		pixel.x = game->map->player.coord.x * game->box_size;
		while (pixel.x < (int)((game->map->player.coord.x + 1)
			* game->box_size))
		{
			my_mlx_pixel_put(&game->img, pixel.x, pixel.y,
				get_color_from_sprite(game,
					&game->sprites[SPRITE_ERMANGO], &pixel));
			pixel.x++;
		}
		pixel.y++;
	}
}

static void	draw_entity(t_game *game, t_point *point)
{
	t_point	pixel;
	size_t	pos;

	pos = (game->win_size.height - (game->map->heigth * game->box_size)) / 2;
	pos = 0;
	pixel.y = point->y * game->box_size + pos;
	while (pixel.y < (int)((point->y + 1) * game->box_size + pos))
	{
		pixel.x = point->x * game->box_size;
		while (pixel.x < (int)((point->x + 1) * game->box_size))
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
	mlx_string_put(game->mlx, game->mlx_win, game->win_size.width / 2,
		10, 0xd9c407, ft_itoa(game->map->player.step));
	return (0);
}

int	draw_background(t_game *game)
{
	t_point	pixel_bg;

	pixel_bg.y = 0;
	while (pixel_bg.y < game->win_size.height)
	{
		pixel_bg.x = 0;
		while (pixel_bg.x < game->win_size.width)
		{
			my_mlx_pixel_put(&game->img, pixel_bg.x, pixel_bg.y,
				get_color_from_sprite(game, &game->sprites[SPRITE_PATH],
					&pixel_bg));
			pixel_bg.x++;
		}
		pixel_bg.y++;
	}
	return (1);
}
