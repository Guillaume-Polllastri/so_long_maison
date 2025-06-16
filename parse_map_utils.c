/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpollast <gpollast@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 16:01:34 by gpollast          #+#    #+#             */
/*   Updated: 2025/06/16 11:54:56 by gpollast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include <fcntl.h>
#include "libft.h"
#include "ft_printf.h"

static void	fill(t_map *map, int row, int col)
{
	t_elem  target;
    t_elem  **tab;
    t_point size;

    tab = map->data;
    target = map->data[map->player.y][map->player.x];
    size.y = map->heigth;
    size.x = map->width;
	if (row < 0 || col < 0 || row >= size.y || col >= size.x)
		return;
	if (tab[row][col] == WALL || (tab[row][col] != COLLECTIBLE  && tab[row][col] != EXIT && tab[row][col] != target))
		return;
    if (tab[row][col] == COLLECTIBLE)
    {
        map->nb_collect++;
    }
	tab[row][col] = WALL;
	fill(map, row -1, col); // fill cell above
	fill(map, row +1, col); // fill cell below
	fill(map, row, col - 1); // fill cell to the left
	fill(map, row, col + 1); // fill cell to the right
}

void	flood_fill(t_map *map)
{
    int row;
    int col;

    row = map->player.y;
	col = map->player.x;
	fill(map, row, col);
}
