/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpollast <gpollast@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 23:12:28 by gpollast          #+#    #+#             */
/*   Updated: 2025/06/24 23:28:45 by gpollast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include <stdlib.h>

void	map_destroy(t_map *map)
{
	size_t	y;

	y = 0;
	while (y < map->heigth)
	{
		free(map->data[y]);
		y++;
	}
	free(map->data);
}
