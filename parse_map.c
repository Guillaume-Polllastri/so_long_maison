/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpollast <gpollast@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/09 10:13:32 by gpollast          #+#    #+#             */
/*   Updated: 2025/06/12 14:43:43 by gpollast         ###   ########.fr       */
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
			map->player.x = i;
			map->player.y = map->heigth;
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

static int	check_wall(t_map *map)
{
	
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
	return (1);
}
//TODO Gerer les rectangles et que ya des murs