#include "index.h"

float	check_border(float y, float yindex) {
	return ((y + yindex) / 512.0);
}

t_rayinfo	print_line(t_vars *mlx, float degrees, float x, float y) 
{
	float		dx;
	float		dy;
	int			sky_y;
	float		lenth;
	float		fish_fix;
	float		cubx;
	float		cuby;
	t_rayinfo	ray;
	static int			ray_index;
	int color;

	ray.x = 2;
	ray.y = -2;
	dy = -cos(degrees * RAD);
	dx = sin(degrees * RAD);
	while (mlx->player.x + ray.x < 100000 && mlx->player.y + ray.y < 100000 && mlx->player.x + ray.x > 0 && mlx->player.y + ray.y > 0 && !check_cube(mlx, mlx->player.x + ray.x, mlx->player.y + ray.y))
	{
		//my_mlx_pixel_put(&mlx->img, (double)mlx->player.x + x,  (double)mlx->player.y + y, 0x0000FF00);
		ray.x += dx;
		ray.y += dy;
		//my_mlx_pixel_put(&mlx->img, (ray_index), 500 - y , color);
	}
	fish_fix = cos((degrees - mlx->degrees) * RAD);
	lenth = sqrt(pow(ray.y, 2.0) + pow(ray.x, 2.0));
	ray.ray_len = lenth * fish_fix;
	++ray_index;
	if (ray_index > 500)
		ray_index = 0;
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

int	draw_sky(t_vars *mlx, float y, int ray_index)
{
	int color;
	
	color = 0x00bfff;
	while (y < WIN_H - mlx->sky)
	{
		my_mlx_pixel_put(&mlx->img, (ray_index),  500 - y, color);
		++y;
	}
	return (0);
}

int	draw_floor(t_vars *mlx, float y, int ray_index)
{
	int color;
	
	color = 0x505050;
	while (y < WIN_H - (WIN_H - mlx->sky))
	{
		my_mlx_pixel_put(&mlx->img, (ray_index),  500 + y, color);
		++y;
	}
	return (0);
}

void ray_cast(t_rayinfo ray, int ray_index, t_vars *mlx)
{
	float		y;
	float		texture_y = 0 ;
	static int	old_wall;
	int			new_wall;
	int			color;
	int			color2;
	float 		cubx;
	float 		cuby;
	t_data		texture;

	y = 0;
	new_wall = 300000 / ray.ray_len;
	
	cubx = (ray.x + mlx->player.x) / 512.0 ; // какой куб по Х по счету
	cuby = (ray.y + mlx->player.y) / 512.0; // какой куб по У по счету
	if (old_wall == 0)
		old_wall = cubx;
	texture = mlx->texture;
	if (mlx->player.y > ray.y + mlx->player.y)
		texture = mlx->texture1;
	// if (ray_index == 500)
	// 	printf("-:%f +:%f %f\n", floor(ray.y + 1 + mlx->player.y) / 512, floor(ray.y - 1 + mlx->player.y) / 512, floor(check_border(ray.y, mlx->player.y)));
	if ((int)floor(ray.y + 1 + mlx->player.y) / 512 == (int)floor(check_border(ray.y, mlx->player.y)) && (int)floor(ray.y - 1 + mlx->player.y) / 512 == (int)floor(check_border(ray.y, mlx->player.y)))
	{
		cubx = cuby;
		texture = mlx->texture2;
		if (mlx->player.x > ray.x + mlx->player.x)
			texture = mlx->texture3;
	}
	y = 0;
	while (y < WIN_H - 500 && y < new_wall)
	{
		color = get_pixel(&texture, (cubx - floor(cubx)) * 128 ,  (y ) / new_wall * 128);
		color2 = get_pixel(&texture, (cubx - floor(cubx)) * 128 + 256,  (y ) / new_wall * 128 + 256);
		my_mlx_pixel_put(&mlx->img, (ray_index), 500 - y , color);
		my_mlx_pixel_put(&mlx->img, (ray_index),  500 + y, color2);
		old_wall = cubx;
		++y;
	}
	draw_sky(mlx, y, ray_index);
	draw_floor(mlx, y, ray_index);
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