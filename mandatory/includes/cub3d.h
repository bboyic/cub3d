#ifndef CUBE3D_H
# define	CUBE3D_H

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