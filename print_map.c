/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpollast <gpollast@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 13:37:24 by gpollast          #+#    #+#             */
/*   Updated: 2025/06/09 16:07:36 by gpollast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include "ft_printf.h"

int	print_map(t_map *map)
{
	size_t	x;
	size_t	y;

	y = 0;
	ft_printf("heigth %d\n", map->heigth);
	ft_printf("width %d\n", map->width);
	while (y < map->heigth)
	{
		x = 0;
		while (x < map->width)
		{
			ft_printf("%c", map->data[y][x] + '0');
			x++;
		}
		ft_printf("\n");
		y++;
	}
	return (0);
}