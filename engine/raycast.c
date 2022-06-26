#include "index.h"

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

void ray_cast(float ray_len, int ray_index, t_vars *mlx)
{
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