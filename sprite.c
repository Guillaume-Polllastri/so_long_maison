/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpollast <gpollast@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 10:50:38 by gpollast          #+#    #+#             */
/*   Updated: 2025/06/23 11:21:22 by gpollast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include "mlx.h"
#include "libft.h"

void    sprite_init(t_game *game)
{
	game->asset.img = mlx_xpm_file_to_image(game->mlx, "sprites/arbres.xpm",
			&game->asset.size.width, &game->asset.size.height);
	game->sprites[SPRITE_WATER].buffer = (int *) mlx_get_data_addr(game->asset.img,
			&game->asset.bits_per_pixel, &game->asset.line_length,
			&game->asset.endian);
	game->sprites[SPRITE_WATER].coord.x = 0;
	game->sprites[SPRITE_WATER].coord.y = 0;
	ft_memcpy(&game->sprites[SPRITE_WATER].size, &game->asset.size, sizeof(t_size));
}