/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpollast <gpollast@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 10:50:38 by gpollast          #+#    #+#             */
/*   Updated: 2025/06/20 15:07:10 by gpollast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include "mlx.h"

void    sprite_init(t_game *game)
{
    game->img.img = mlx_xpm_file_to_image(game->mlx, "sprites/Grass.xpm",
        &game->sprite.size.width, &game->sprite.size.height);
    game->sprite.buffer = (int *) mlx_get_data_addr(game->img.img,
        &game->img.bits_per_pixel, &game->img.line_length, &game->img.endian);
}