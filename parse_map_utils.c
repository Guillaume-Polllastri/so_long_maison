/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpollast <gpollast@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 16:01:34 by gpollast          #+#    #+#             */
/*   Updated: 2025/06/24 23:33:40 by gpollast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include <fcntl.h>
#include "libft.h"
#include "ft_printf.h"
#include <stdlib.h>

static int	fill(t_map *map, int row, int col)
{
	t_elem	**tab;
	t_point	size;

	tab = map->data;
	size.y = map->heigth;
	size.x = map->width;
	if (row < 0 || col < 0 || row >= size.y || col >= size.x)
		return (0);
	if (tab[row][col] == WALL)
		return (0);
	if (tab[row][col] == COLLECTIBLE)
	{
		map->nb_test_collectible++;
	}
	if (tab[row][col] == EXIT)
	{
		map->nb_test_exit++;
	}
	tab[row][col] = WALL;
	fill(map, row -1, col);
	fill(map, row +1, col);
	fill(map, row, col - 1);
	fill(map, row, col + 1);
	return (1);
}

static t_map	*init_copy_map(t_map *map)
{
	t_map	*copy;

	if (!map || !map->data)
		return (NULL);
	copy = malloc(sizeof(t_map));
	if (!copy)
		return (NULL);
	copy->width = map->width;
	copy->heigth = map->heigth;
	copy->nb_test_collectible = 0;
	copy->nb_test_exit = 0;
	copy->data = malloc(sizeof(t_elem *) * copy->heigth);
	if (!copy->data)
	{
		free(copy);
		return (NULL);
	}
	return (copy);
}

static t_map	*copy_map(t_map *map)
{
	t_map	*copy;
	size_t	y;
	size_t	x;

	copy = init_copy_map(map);
	y = 0;
	while (y < map->heigth)
	{
		copy->data[y] = malloc(sizeof(t_elem) * copy->width);
		if (!copy->data[y])
		{
			while (y > 0)
				free(copy->data[--y]);
			return (free(copy->data), free(copy), NULL);
		}
		x = 0;
		while (x < map->width)
		{
			copy->data[y][x] = map->data[y][x];
			x++;
		}
		y++;
	}
	return (copy);
}

int	flood_fill(t_map *map)
{
	int		row;
	int		col;
	t_map	*map_cpy;

	row = map->player.coord.y;
	col = map->player.coord.x;
	map_cpy = copy_map(map);
	if (!fill(map_cpy, row, col))
	{
		map_destroy(map_cpy);
		return (free(map_cpy), 0);
	}
	if ((map_cpy->nb_test_collectible != map->nb_collect)
		|| (map_cpy->nb_test_exit != map->nb_exit))
	{
		map_destroy(map_cpy);
		return (free(map_cpy), 0);
	}
	map_destroy(map_cpy);
	free(map_cpy);
	return (1);
}
