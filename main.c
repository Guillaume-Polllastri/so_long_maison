/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpollast <gpollast@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 10:13:23 by gpollast          #+#    #+#             */
/*   Updated: 2025/06/22 20:22:37 by gpollast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include "libft.h"

int	main(void)
{
	t_map	map;
	t_game	game;

	if (!parse_map(&map, "maps/map1.ber"))
		return (1);
	// print_map(&map);
	if (!game_init(&game, &map))
		return (1);
	if (!game_open_window(&game, 1300, 600))
		return (1);
	if (!game_loop(&game))
		return (1);
	return (0);
}
