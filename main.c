/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpollast <gpollast@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 10:13:23 by gpollast          #+#    #+#             */
/*   Updated: 2025/06/06 16:46:11 by gpollast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42.h"
#include "list.h"
#include "get_next_line.h"
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#define WIDTH 800
#define HEIGHT 600

void	put_case(t_data img, int x, int y, char c)
{
	if (c == '0')
		mlx_put_pixel(img.img, x, y, 0x47d578);
	if (c == '1')
		mlx_put_pixel(img.img, x, y, 0x137f38);
	if (c == 'C')
		mlx_put_pixel(img.img, x, y, 0xecec2b);
	if (c == 'P')
		mlx_put_pixel(img.img, x, y, 0xFFFFFF);
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

int	count_sizex_map(int fd)
{
	int	count;

	count = (int) ft_strlen(get_next_line(fd));
	return (count - 1);
}

void	write_map(t_data img, int size_x, int size_y)
{
	int		x;
	int		y;
	int		i;
	int		j;
	char	*line;
	char	c;
	int		fd;

	j = 1;
	fd = open("maps/map1.ber", O_RDONLY);
	while (j <= size_y)
	{
		i = 1;
		x = 0;
		line = get_next_line(fd);
		if (!line)
			return ;
		while (i <= size_x)
		{
			c = line[i - 1];
			while (x < (i *(WIDTH / size_x)))
			{
				y = (j - 1) * (HEIGHT / size_y);
				while (y < (j * (HEIGHT / size_y)))
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

void	write_case(t_data img, t_coord size_case, t_coord pos, char c)
{
	while (pos.x < size_case.x)
	{
		while (pos.y < size_case.y)
		{
			put_case(img, pos.x, pos.y, c);
			pos.y = pos.y + 1;
		}
		pos.x = pos.x + 1;
	}
}

void my_loop_hook(void* param) 
{
    mlx_t*	mlx;
	
	mlx = (mlx_t*) param;
    if (mlx_is_mouse_down(mlx, MLX_MOUSE_BUTTON_LEFT))
	{
		printf("%s", "LEFT");
	}
	if (mlx_is_key_down(mlx, MLX_KEY_W))
	{
		printf("%s", "W");
	}
	if (mlx_is_key_down(mlx, MLX_KEY_A))
	{
		printf("%s", "A");
	}
	if (mlx_is_key_down(mlx, MLX_KEY_D))
	{
		printf("%s", "D");
	}
	if (mlx_is_key_down(mlx, MLX_KEY_S))
	{
		printf("%s", "S");
	}
}

int	main(void)
{
	mlx_t		*mlx;
	t_data		img;
	int			size_x;
	int			size_y;
	int			fd;

	fd = open("maps/map1.ber", O_RDONLY);
	size_x = count_sizex_map(fd);
	size_y = count_sizey_map(fd) + 1;
	mlx = mlx_init(WIDTH, HEIGHT, "toto", true);
	if (!mlx)
		return (EXIT_FAILURE);
	img.img = mlx_new_image(mlx, WIDTH, HEIGHT);
	write_map(img, size_x, size_y);
	mlx_image_to_window(mlx, img.img, 0, 0);
	mlx_loop_hook(mlx, my_loop_hook, mlx);
	mlx_loop(mlx);
	printf("x %d\n", size_x);
	printf("y %d\n", size_y);
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}
