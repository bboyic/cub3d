#include <stdio.h>
#include <mlx.h>
#include <math.h>

#define PI 3.14159265359
#define RAD 0.0174533

typedef struct	s_data 
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

typedef struct s_player {
	float	x;
	float	y;
	float	dx;
	float	dy;
	float	da;
}	t_player;

typedef struct s_vars 
{
	float		degrees;
	int			front;
	int			turn_left;
	int			turn_right;
	int			back;
	int			left;
	int			right;
	int			sprint;
	char		**map;
	void		*mlx;
	void		*mlx_win;
	t_player	player;
	t_data		img;
}	t_vars;

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

int	key_hook(int keycode, t_vars *game)
{
	//printf("Hello from key_hook %d!\n", keycode);
	if (keycode == 0)
		game->left = 1;
	if (keycode == 1)
		game->back = 1;
	if (keycode == 2)
		game->right = 1;
	if (keycode == 13)
		game->front = 1;
	if (keycode == 257)
		game->sprint = 2;
	if (keycode == 12)
		game->turn_left = 1;
	if (keycode == 14)
		game->turn_right = 1;
	return (0);
}

int	key_down(int keycode, t_vars *mlx)
{
	//printf("Hello from key_hook %d!\n", keycode);
	if (keycode == 0)
		mlx->left = 0;
	if (keycode == 1)
		mlx->back = 0;
	if (keycode == 2)
		mlx->right = 0;
	if (keycode == 13)
		mlx->front = 0;
	if (keycode == 257)
		mlx->sprint = 1;
	if (keycode == 12)
		mlx->turn_left = 0;
	if (keycode == 14)
		mlx->turn_right = 0;
	return (0);
}

int	check_cube(t_vars *mlx, int x, int y)
{
	if (y / 16 < 8 && x / 16 < 12 && mlx->map[y / 16][x / 16] == '1')
		return (1);
	else
		return (0);
}

void	draw_background(t_vars *mlx)
{
	int	max_x;
	int	max_y;
	int	x;
	int	y;

	max_y = 300;
	max_x = 1000;
	y = 0;
	while (y < max_y)
	{
		x = 0;
		while (x < max_x)
		{
			if (check_cube(mlx, x, y))
			{
				my_mlx_pixel_put(&mlx->img, x, y, 0x000000FF);
			} 
			else
				my_mlx_pixel_put(&mlx->img, x, y, 0x00000000);
			++x;
		}
		++y;
	}
}

void	draw_player(t_vars *mlx)
{
	int		x;
	int		y;

	y = 0;
	while (y < 5) 
	{
		x = 0;
		while (x < 5)
		{
			my_mlx_pixel_put(&mlx->img, mlx->player.x + x, mlx->player.y + y, 0x00FF0000);
			++x;
		}
		++y;
	}
}

void	sample_move(t_vars *mlx)
{
	if (mlx->front == 1)
	{
		mlx->player.x += mlx->player.dx * mlx->sprint; 
		mlx->player.y -= mlx->player.dy * mlx->sprint;
	}
	if (mlx->back == 1)
	{
		mlx->player.x -= mlx->player.dx * mlx->sprint; 
		mlx->player.y += mlx->player.dy * mlx->sprint;
	}
	if (mlx->left == 1)
	{
		mlx->player.x -= mlx->player.dy * mlx->sprint;
		mlx->player.y -= mlx->player.dx * mlx->sprint;
	}
	if (mlx->right == 1)
	{
		mlx->player.x += mlx->player.dy * mlx->sprint;
		mlx->player.y += mlx->player.dx * mlx->sprint;
	}
}

void	turn_move(t_vars *mlx)
{
	if (mlx->turn_left == 1)
	{
		mlx->degrees -= 2;
		mlx->player.dy = cos(mlx->degrees * RAD);
		mlx->player.dx = sin(mlx->degrees * RAD);
		if (mlx->degrees <= 0)
			mlx->degrees = 360;
	}
	if (mlx->turn_right == 1)
	{
		mlx->degrees += 2;
		mlx->player.dy = cos(mlx->degrees * RAD);
		mlx->player.dx = sin(mlx->degrees * RAD);
		if (mlx->degrees >= 360)
			mlx->degrees = 0;
	}
}

void	check_move(t_vars *mlx)
{
	sample_move(mlx);
	turn_move(mlx);
}

float	print_line(t_vars *mlx, float degrees, double x, double y) 
{
	double	dx;
	double	dy;
	float	lenth;
	float	fish_fix;

	x = 2;
	y = -2;
	dy = -cos(degrees * RAD);
	dx = sin(degrees * RAD);
	while (mlx->player.x + x < 1000 && mlx->player.y + y < 300 && mlx->player.x + x > 0 && mlx->player.y + y > 0 && !check_cube(mlx, mlx->player.x + x, mlx->player.y + y))
	{
		my_mlx_pixel_put(&mlx->img, (double)mlx->player.x + x,  (double)mlx->player.y + y, 0x0000FF00);
		x += dx;
		y += dy;
	}
	fish_fix = cos((degrees - mlx->degrees) * RAD);
	lenth = sqrt(pow(y, 2.0) + pow(x, 2.0)) ;
	return (lenth * fish_fix);
}

void ray_cast(float ray_len, int ray_index, t_vars *mlx) {
	int y;

	y = 0;
	while (y < 100 && y < 2000 / (int)ray_len)
	{
		my_mlx_pixel_put(&mlx->img, 500 + (ray_index), 100 - y , 0x0000FF00);
		my_mlx_pixel_put(&mlx->img, 500 + (ray_index),  100 + y , 0x0000FF00);
		++y;
	}
}

void	draw_ray(t_vars *mlx)
{
	int	ray_len;
	float ray_index;
	float degrees;

	ray_index = 0;
	degrees = mlx->degrees;
	if (degrees >= 360)
		degrees = 0;
	if (degrees <= 0)
		degrees = 360;
	ray_len = 0;
	while (ray_len++ < 500)
	{
		//ray_cast(print_line(mlx, degrees, mlx->player.x, mlx->player.y), ray_index + 60, mlx);
		ray_cast(print_line(mlx, degrees - 15, mlx->player.x, mlx->player.y), ray_index, mlx);
		ray_index += 0.5;
		degrees += 0.1;

		// if (degrees > 360 || degrees < 0)
		// 	printf("ERROR1 %f\n", degrees);
		// if (degrees > 360 || degrees < 0)
		// 	printf("ERROR1\n");
	}
}

int	render_next_frame(void *data) {
	t_vars *mlx;

	mlx = (t_vars *)data;
	check_move(mlx);
	draw_background(mlx);
	draw_player(mlx);
	draw_ray(mlx);
	mlx_put_image_to_window(mlx->mlx, mlx->mlx_win, mlx->img.img, 0, 0);
	return (0);
}

void	palyer_init(t_vars *mlx)
{
	mlx->degrees = 0;
	mlx->player.da = 0;
	mlx->player.dy = cos(0);
	mlx->player.dx = sin(0);
	mlx->player.x = 150;
	mlx->player.y = 150;
	mlx->front = 0;
	mlx->back = 0;
	mlx->left = 0;
	mlx->right = 0;
	mlx->sprint = 1;
	mlx->turn_left = 0;
	mlx->turn_right = 0;
	mlx->map[0] = "111111111111";
	mlx->map[1] = "100000000001";
	mlx->map[2] = "100100100001";
	mlx->map[3] = "100100000001";
	mlx->map[4] = "100100100001";
	mlx->map[5] = "100000000001";
	mlx->map[6] = "100010010001";
	mlx->map[7] = "111111111111";
}

void	my_mlx_init(t_vars *mlx)
{
	mlx->mlx = mlx_init();
	mlx->mlx_win = mlx_new_window(mlx->mlx, 1000, 300, "Hello world!");
	mlx->img.img = mlx_new_image(mlx->mlx, 1000, 300);
	mlx->img.addr = mlx_get_data_addr(mlx->img.img, &(mlx->img.bits_per_pixel), &(mlx->img.line_length),
								&(mlx->img.endian));
	palyer_init(mlx);
	mlx_hook(mlx->mlx_win, 2, 1L<<0, key_hook, mlx);
	mlx_key_hook(mlx->mlx_win, key_down, mlx);
	mlx_loop_hook(mlx->mlx, render_next_frame, mlx);
	mlx_loop(mlx->mlx);
}

int	main(void) 
{
	t_vars mlx;
	my_mlx_init(&mlx);
	printf("hey it is check static param = %d\n", mlx.back);
	return (0);
}