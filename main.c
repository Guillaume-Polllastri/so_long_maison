/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpollast <gpollast@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 10:13:23 by gpollast          #+#    #+#             */
/*   Updated: 2025/06/23 23:08:33 by gpollast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include "libft.h"
#include "stdlib.h"

int	main(void)
{
	t_map	map;
	t_game	game;

	if (!parse_map(&map, "maps/map3.ber"))
		return (1);
	if (!game_init(&game, &map))
		return (1);
	if (!game_open_window(&game, 1300, 600))
		return (1);
	if (!game_loop(&game))
		return (1);
	game_destroy(&game);
	return (0);
}
