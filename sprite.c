/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpollast <gpollast@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 10:50:38 by gpollast          #+#    #+#             */
/*   Updated: 2025/06/24 18:01:59 by gpollast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include "mlx.h"
#include "libft.h"

void	sprite_init(t_game *game, char *path, int id)
{
	game->sprites->asset.img = mlx_xpm_file_to_image(game->mlx, path,
			&game->sprites->asset.size.width,
			&game->sprites->asset.size.height);
	game->sprites[id].buffer = (int *)
		mlx_get_data_addr(game->sprites->asset.img,
			&game->sprites->asset.bits_per_pixel,
			&game->sprites->asset.line_length,
			&game->sprites->asset.endian);
	ft_memcpy(&game->sprites[id].size,
		&game->sprites->asset.size, sizeof(t_size));
}

int	get_color_from_sprite(t_game *game, t_sprite *sprite,
		t_point *pixel)
{
	int	pixel_sprite_x;
	int	pixel_sprite_y;
	int	pixel_sprite;
	int	calcul_x;
	int	calcul_y;

	pixel_sprite_x = (pixel->x % game->box_size);
	pixel_sprite_y = (pixel->y % game->box_size);
	calcul_x = (pixel_sprite_x * sprite->size.width) / game->box_size;
	calcul_y = (pixel_sprite_y * sprite->size.height) / game->box_size;
	pixel_sprite = (calcul_y * sprite->size.width) + calcul_x;
	return (sprite->buffer[pixel_sprite]);
}

void	draw_color(t_game *game, t_point *point, t_point *pixel)
{
	if (game->map->data[point->y][point->x] == WALL)
		my_mlx_pixel_put(&game->img, pixel->x, pixel->y,
			get_color_from_sprite(game, &game->sprites[SPRITE_TREE], pixel));
	else if (game->map->data[point->y][point->x] == PATH)
		my_mlx_pixel_put(&game->img, pixel->x, pixel->y,
			get_color_from_sprite(game, &game->sprites[SPRITE_PATH], pixel));
	else if (game->map->data[point->y][point->x] == COLLECTIBLE)
		my_mlx_pixel_put(&game->img, pixel->x, pixel->y,
			get_color_from_sprite(game, &game->sprites[SPRITE_MANGO], pixel));
	else if (game->map->data[point->y][point->x] == EXIT)
		my_mlx_pixel_put(&game->img, pixel->x, pixel->y,
			get_color_from_sprite(game, &game->sprites[SPRITE_HOLE], pixel));
}
