/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpollast <gpollast@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 10:13:32 by gpollast          #+#    #+#             */
/*   Updated: 2025/06/20 11:04:28 by gpollast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include <fcntl.h>
#include "get_next_line.h"
#include "libft.h"
#include "ft_printf.h"

static size_t	ft_strlen_no_nl(char *str)
{
	size_t	i;

	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	return (i);
}

static int	parse_line(t_map *map, char *line)
{
	int		i;

	map->data = ft_realloc(map->data, map->heigth, map->heigth + 1,
			sizeof(t_elem *));
	if (!map->data)
		return (0);
	i = 0;
	map->data[map->heigth] = malloc(sizeof(t_elem) * map->width);
	while (line[i])
	{
		if (line[i] == '0')
			map->data[map->heigth][i] = PATH;
		else if (line[i] == '1')
			map->data[map->heigth][i] = WALL;
		else if (line[i] == 'P')
		{
			map->player.coord.x = i;
			map->player.coord.y = map->heigth;
			map->nb_player++;
			map->data[map->heigth][i] = PATH;
		}
		else if (line[i] == 'C')
		{
			map->nb_collect++;
			map->data[map->heigth][i] = COLLECTIBLE;
		}
		else if (line[i] == 'E')
		{
			map->end.x = i;
			map->end.y = map->heigth;
			map->nb_exit++;
			map->data[map->heigth][i] = EXIT;
		}
		else if (line[i] == 'M')
			map->data[map->heigth][i] = MONSTER;
		else if (line[i] != '\n')
		{
			ft_printf("Read error, unknown element : %c\n", line[i]);
			return (0);
		}
		i++;
	}
	map->heigth += 1;
	return (1);
}

static int	check_nb_entity(t_map *map)
{
	if (map->nb_player != 1)
	{
		ft_printf("The game requires 1 Player\n");
		return (0);
	}
	if (map->nb_exit != 1)
	{
		ft_printf("The game requires 1 Exit\n");
		return (0);
	}
	if (!map->nb_collect)
	{
		ft_printf("The game requires at least 1 Collectible\n");
		return (0);
	}
	if (map->heigth == map->width)
	{
		ft_printf("Size of the map is not a rectangle\n");
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
			ft_printf("La map n'est pas entoure de mur\n");	
			return (0);
		}
		i++;
	}
	i = 1;
	while (i < map->heigth)
	{
		if ((map->data[i][0] != WALL) || (map->data[i][map->width -1] != WALL))
		{
			ft_printf("La map n'est pas entoure de mur\n");
			return (0);
		}
		i++;
	}
	return (1);
}

int	parse_map(t_map *map, char *path)
{
	int		fd;
	char	*line;

	ft_bzero(map, sizeof(*map));
	fd = open(path, O_RDONLY);
	line = get_next_line(fd);
	map->width = ft_strlen_no_nl(line);
	while (line)
	{
		if (ft_strlen_no_nl(line) != map->width)
		{
			ft_printf("Read error, map size is incorrect\n");
			return (0);
		}
		if (!parse_line(map, line))
			return (0);
		line = get_next_line(fd);
	}
	if (!check_wall(map))
		return (0);
	if (!check_nb_entity(map))
		return (0);
	if (!flood_fill(map))
	{
		ft_printf("Collectible or exit are not accessible\n");
		return (0);
	}
	return (1);
}
//TODO Gerer les rectangles