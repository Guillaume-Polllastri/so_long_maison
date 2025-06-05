/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpollast <gpollast@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 10:13:23 by gpollast          #+#    #+#             */
/*   Updated: 2025/06/05 09:19:28 by gpollast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42.h"
#include "get_next_line.h"
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#define WIDTH 800
#define HEIGHT 600

typedef struct	s_data {
	mlx_image_t	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

typedef enum {
	EMPTY = '0',
	WALL = '1',
	COLLECTIBLE = 'C',
	PLAYER = 'P',
	ENNEMY = 'E'
}	elem_t;

void	put_case(t_data img, int x, int y, char c)
{
	if (c == '0')
		mlx_put_pixel(img.img, x, y, 0x47d578);
	if (c == '1')
		mlx_put_pixel(img.img, x, y, 0x137f38);
	if (c == 'C')
		mlx_put_pixel(img.img, x, y, 0xecec2b);
	if (c == 'P')
		mlx_put_pixel(img.img, x, y, 0x1d7f13);
	if (c == 'E')
		mlx_put_pixel(img.img, x, y, 0x7f3013);
}

int	count_sizey_map(int fd)
{
	char	*line;
	int		count;

	count = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
		{
			close(fd);			
			return (count);
		}
		count++;
	}
	close(fd);
	return (count);
}

void	write_case_x(t_data img, int size_x, int size_y)
{
	int		x;
	int		y;
	int		i;
	int		j;
	char	*line;
	char	c;

	j = 1;
	while (j <= size_y)
	{
		i = 1;
		x = 0;
		line = get_next_line(open("maps/map1.ber", O_RDONLY));
		if (!line)
			return ;
		while (i <= size_x)
		{
			c = line[i - 1];
			while (x < (i *(WIDTH / size_x)))
			{
				y = (i - 1) * (HEIGHT / size_y);
				while (y < (1 * (HEIGHT / size_y)))
				{
					put_case(img, x, y, c);
					y++;
				}
				x++;
			}
			i++;
		}
		j++;
	}
}

int	main(void)
{
	mlx_t		*mlx;
	t_data		img;
	int			size_x;
	int			size_y;

	mlx = mlx_init(WIDTH, HEIGHT, "toto", true);
	if (!mlx)
		return (EXIT_FAILURE);
	img.img = mlx_new_image(mlx, WIDTH, HEIGHT);
	size_x = 13;
	size_y = 5;
	// while (x < WIDTH)
	// {
	// 	y = 0;
	// 	while (y < HEIGHT)
	// 	{
	// 		mlx_put_pixel(img.img, x, y, 0x001f997f);
	// 		y++;
	// 	}
	// 	x++;
	// }
	write_case_x(img, size_x, size_y);
	mlx_image_to_window(mlx, img.img, 0, 0);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}
