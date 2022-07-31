#ifndef CUB3D_H
#define	CUB3D_H

typedef struct s_data
{
	void *img;
	char *addr;
	int bits_per_pixel;
	int line_length;
	int endian;
} t_data;

typedef struct s_obj
{
	int x;
	int y;
} t_obj;

typedef struct s_player {
	float	x;
	float	y;
	float	dx;
	float	dy;
	float	da;
	float	degrees;
}	t_player;

typedef struct s_coin {
	int	x;
	int	y;
	// TODO:add field for sprite
}	t_coin;

typedef struct s_door {
	int		x;
	int		y;
	int		unlock;
	char	side;
	// TODO:add field for sprite
}	t_door;

// first node is temp for correct order and have null params
typedef struct s_list
{
	void			*key;
	struct s_list	*next;
}					t_list;

typedef struct s_dict
{
	int		len;
	char	*line;
}		t_dict;

typedef struct s_map
{
	char	*texture_of_north;
	char	*texture_of_south;
	char	*texture_of_west;
	char	*texture_of_east;
	int		rgb_floor[3];
	int		rgb_ceiling[3];
	t_dict	**mmap;
	int		height;
}			t_map;

typedef struct s_vars 
{
	int			sky;
	float		degrees;
	int			front;
	int			turn_left;
	int			turn_right;
	int			back;
	int			left;
	int			right;
	int			sprint;
	t_map		*map_data;
	t_data		texture;
	void		*mlx;
	void		*mlx_win;
	t_player	player;
	t_coin		*coins;
	int			coins_count;
	t_door		door;
	t_data		img;
}	t_vars;

typedef struct s_rayinfo {
	float	ray_len;
	float	x;
	float	y;
} t_rayinfo;

#endif