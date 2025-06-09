#include "mlx.h"

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

typedef struct  s_coord {
    int x;
    int y;
}   t_coord;
