/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpollast <gpollast@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 10:50:38 by gpollast          #+#    #+#             */
/*   Updated: 2025/06/26 13:40:31 by gpollast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include "mlx.h"
#include "libft.h"

int	sprite_init(t_game *game, char *path, int id)
{
	game->sprites[id].asset.img = mlx_xpm_file_to_image(game->mlx, path,
			&game->sprites[id].asset.size.width,
			&game->sprites[id].asset.size.height);
	if (!game->sprites[id].asset.img)
		return (0);
	game->sprites[id].buffer = (int *)
		mlx_get_data_addr(game->sprites[id].asset.img,
			&game->sprites[id].asset.bits_per_pixel,
			&game->sprites[id].asset.line_length,
			&game->sprites[id].asset.endian);
	ft_memcpy(&game->sprites[id].size,
		&game->sprites[id].asset.size, sizeof(t_size));
	return (1);
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
		set_pixel(&game->img, pixel->x, pixel->y,
			get_color_from_sprite(game, &game->sprites[SPRITE_TREE], pixel));
	else if (game->map->data[point->y][point->x] == PATH)
		set_pixel(&game->img, pixel->x, pixel->y,
			get_color_from_sprite(game, &game->sprites[SPRITE_PATH], pixel));
	else if (game->map->data[point->y][point->x] == COLLECTIBLE)
		set_pixel(&game->img, pixel->x, pixel->y,
			get_color_from_sprite(game, &game->sprites[SPRITE_MANGO], pixel));
	else if (game->map->data[point->y][point->x] == EXIT)
		set_pixel(&game->img, pixel->x, pixel->y,
			get_color_from_sprite(game, &game->sprites[SPRITE_HOLE], pixel));
}
