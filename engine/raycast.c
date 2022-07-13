#include "index.h"

t_rayinfo	print_line(t_vars *mlx, float degrees, float x, float y) 
{
	float		dx;
	float		dy;
	float		lenth;
	float		fish_fix;
	t_rayinfo	ray;

	x = 2;
	y = -2;
	dy = -cos(degrees * RAD);
	dx = sin(degrees * RAD);
	while (mlx->player.x + x < 100000 && mlx->player.y + y < 100000 && mlx->player.x + x > 0 && mlx->player.y + y > 0 && !check_cube(mlx, mlx->player.x + x, mlx->player.y + y))
	{
		//my_mlx_pixel_put(&mlx->img, (double)mlx->player.x + x,  (double)mlx->player.y + y, 0x0000FF00);
		x += dx;
		y += dy;
	}
	fish_fix = cos((degrees - mlx->degrees) * RAD);
	lenth = sqrt(pow(y, 2.0) + pow(x, 2.0));
	ray.ray_len = lenth * fish_fix;
	ray.x = x;
	ray.y = y;
	return (ray);
}

// int			get_pixel(t_data *img, int x, int y)
// {
// 	int		*dst;
// 	int		color;

// 	dst = (void *)img->addr + (y * img->line_length + x * \
// 												(img->bits_per_pixel / 8));
// 	color = *(int*)dst;
// 	return (color);
// }

void ray_cast(t_rayinfo ray, int ray_index, t_vars *mlx)
{
	int y;
	static int old_wall;
	int	new_wall;
	int	color;
	float cubx;
	float cuby;

	new_wall = 300000 / ray.ray_len;
	if (old_wall == 0)
		old_wall = new_wall;
	y = 0;
	// if (old_wall < new_wall + 1 && old_wall > new_wall - 1)
	// 	new_wall = old_wall;
	// if (new_wall < 500)
	// {
	// 	my_mlx_pixel_put(&mlx->img, (ray_index), 500 - new_wall , 0x0000FF00);
	// 	my_mlx_pixel_put(&mlx->img, (ray_index),  500 + new_wall, 0x0000FF00);
	// 	old_wall = new_wall;
	// }
	// cubx = (ray.x + mlx->player.x) / 512.0 ;
	cubx = (ray.x + mlx->player.x) / 512.0 ; // какой куб по Х по счету
	cuby = (ray.y + mlx->player.y) / 512.0; // какой куб по У по счету
	while (y < WIN_H - 500 && y < new_wall)
	{
		color = 0x0000FF00;
		
		//printf("%d\n", new_wall / 2);
		color = get_pixel(&mlx->texture, (cubx - floor(cubx)) * 512 ,  y * (cuby / 512));
		//color = get_pixel(&mlx->texture, (cuby - floor(cuby)) * 512 ,  y);
		// if (y  > 0)
		// 	printf("%d\n", y);
		//printf("%d\n", mlx->texture.bits_per_pixel);
		//color = 0x0000FF00;
		my_mlx_pixel_put(&mlx->img, (ray_index), 500 - y , color);
		my_mlx_pixel_put(&mlx->img, (ray_index),  500 + y, color);
		old_wall = new_wall;
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
	// if (degrees >= 360)
	// 	degrees = 0;
	// if (degrees <= 0)
	// 	degrees = 360;
	ray_len = 0;
	while (ray_len++ < 1000)
	{
		if (ray_len == 500)
			my_mlx_pixel_put(&mlx->img, 500, 500 , 0x00ff0000);
		//ray_cast(print_line(mlx, degrees, mlx->player.x, mlx->player.y), ray_index + 60, mlx);
		ray_cast(print_line(mlx, degrees - 25, mlx->player.x, mlx->player.y), ray_index, mlx);
		ray_index += 1;
		degrees += 0.05;

		// if (degrees > 360 || degrees < 0)
		// 	printf("ERROR1 %f\n", degrees);
		// if (degrees > 360 || degrees < 0)
		// 	printf("ERROR1\n");
	}
}