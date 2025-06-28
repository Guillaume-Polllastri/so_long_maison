/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpollast <gpollast@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 10:13:23 by gpollast          #+#    #+#             */
/*   Updated: 2025/06/28 22:24:33 by gpollast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include "libft.h"
#include "stdlib.h"
#include "ft_printf.h"

int	main(int ac, char **av)
{
	t_map	map;
	t_game	game;

	if (ac == 2)
	{
		ft_bzero(&game, sizeof(game));
		ft_bzero(&map, sizeof(map));
		if (check_file_extend(av[1]))
			return (1);
		if (!parse_map(&map, av[1]))
			return (1);
		if (!game_init(&game, &map))
			return (1);
		if (!game_open_window(&game, 1300, 600))
			return (1);
		if (!game_loop(&game))
			return (1);
		game_destroy(&game);
	}
	else
	{
		ft_printf("Error\n");
		ft_printf("The program needed only 1 map\n");
	}
	return (0);
}
