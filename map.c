/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpollast <gpollast@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 23:12:28 by gpollast          #+#    #+#             */
/*   Updated: 2025/06/30 17:31:19 by gpollast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include <stdlib.h>
#include "ft_printf.h"

void	map_destroy(t_map *map)
{
	size_t	y;

	y = 0;
	if (!map || !map->data)
		return ;
	while (y < map->heigth)
	{
		free(map->data[y]);
		y++;
	}
	free(map->data);
}

static int	check_nb_entity(t_map *map)
{
	if (map->nb_player != 1)
	{
		ft_printf("Error\nThe game requires 1 Player\n");
		return (0);
	}
	if (map->nb_exit != 1)
	{
		ft_printf("Error\nThe game requires 1 Exit\n");
		return (0);
	}
	if (!map->nb_collect)
	{
		ft_printf("Error\nThe game requires at least 1 Collectible\n");
		return (0);
	}
	return (1);
}

static int	check_wall(t_map *map)
{
	size_t	i;

	i = 0;
	while (i < map->width)
	{
		if ((map->data[0][i] != WALL) ||
			(map->data[map->heigth - 1][i] != WALL))
		{
			ft_printf("Error\nThe map is not surrounded by walls\n");
			return (0);
		}
		i++;
	}
	i = 1;
	while (i < map->heigth)
	{
		if ((map->data[i][0] != WALL) || (map->data[i][map->width -1] != WALL))
		{
			ft_printf("Error\nThe map is not surrounded by walls\n");
			return (0);
		}
		i++;
	}
	return (1);
}

int	check_map(t_map *map)
{
	if (!check_wall(map))
		return (0);
	if (!check_nb_entity(map))
		return (0);
	if (!flood_fill(map))
	{
		ft_printf("Error\nCollectible or exit are not accessible\n");
		return (0);
	}
	return (1);
}
