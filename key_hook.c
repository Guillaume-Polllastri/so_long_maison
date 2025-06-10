/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpollast <gpollast@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 12:50:03 by gpollast          #+#    #+#             */
/*   Updated: 2025/06/10 17:48:04 by gpollast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include "mlx.h"
#include <stdlib.h>
#include <stdio.h>

int	ft_key_hook(int keycode, t_game *game)
{
	if (keycode == ESC)
	{
		mlx_destroy_window(game->mlx, game->mlx_win);
		exit(0);
	}
    if (keycode == W || keycode == UP_ARROW)
    {
        printf("Haut\n");
    }
    if (keycode == A || keycode == LEFT_ARROW)
    {
     printf("Gauche\n");
    }
    if (keycode == S || keycode == DOWN_ARROW)
    {
     printf("Bas\n");
    }
    if (keycode == D || keycode == RIGHT_ARROW)
    {
    printf("Droite\n");
    }
    // printf("%d\n", keycode);
    return (0);
}