/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpollast <gpollast@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 10:13:32 by gpollast          #+#    #+#             */
/*   Updated: 2025/06/28 22:16:18 by gpollast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include <fcntl.h>
#include "get_next_line.h"
#include "libft.h"
#include "ft_printf.h"
#include <stdio.h>

static void	check_player_collect_exit(t_map *map, char *line, int i)
{
	if (line[i] == 'P')
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
	if (!map->data[map->heigth])
		return (free(map->data), 0);
	while (line[i])
	{
		if (line[i] == '0')
			map->data[map->heigth][i] = PATH;
		else if (line[i] == '1')
			map->data[map->heigth][i] = WALL;
		else if (line[i] == 'P' || line[i] == 'C' || line[i] == 'E')
			check_player_collect_exit(map, line, i);
		else if (line[i] != '\n')
		{
			ft_printf("Error\nRead error, unknown element : %c\n", line[i]);
			return (0);
		}
		i++;
	}
	map->heigth += 1;
	return (1);
}

int	parse_map(t_map *map, char *path)
{
	int		fd;
	char	*line;

	ft_bzero(map, sizeof(*map));
	fd = open(path, O_RDONLY);
	line = get_next_line(fd);
	if (!line)
		return (ft_printf("Error\nThere is no map\n"), 0);
	map->width = ft_strlen_no_nl(line);
	while (line)
	{
		if (ft_strlen_no_nl(line) != map->width)
		{
			ft_printf("Error\nRead error, map size is incorrect\n");
			return (free(line), 0);
		}
		if (!parse_line(map, line))
			return (free(line), 0);
		free(line);
		line = get_next_line(fd);
	}
	if (!check_map(map))
		return (0);
	return (1);
}
//TODO Gerer les rectangles