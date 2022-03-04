#ifndef MAIN_H
# define	MAIN_H

#include <mlx.h>
#include <unistd.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define PI 3.14159265359
#define RD 0.0174533

typedef struct	s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

typedef struct	s_obj {
	int	x;
	int	y;
}	t_obj;

typedef struct	s_player {
	float	x;
	float 	y;
	float 	dx;
	float 	dy;
	float	a;
	float	ra;
	int		z;
}	t_player;

typedef struct	s_vars {
	t_data	img;
	t_data	textute;
	t_data	hands;
	void	*mlx;
	void	*win;
	t_player pl;
}	t_vars;

#endif