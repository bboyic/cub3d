#include "index.h"

// I am putting "#define"s here for a while
#define TEXTURE_SIZE (512.0)
#define WALL_ALIGN (256)
#define MAX_RANGE (100000)
#define RATIO_DISPLAY (300000)

float	check_border(float y, float yindex) {
	return ((y + yindex) / TEXTURE_SIZE);
}

t_rayinfo	print_line(t_vars *mlx, float degrees, float x, float y) 
{
	float		dx;
	float		dy;
	float		fish_fix;
	t_rayinfo	ray;
	int			color;

	ray.x = 2;
	ray.y = -2;
	dy = -cos(degrees * RAD); // шаг по у
	dx = sin(degrees * RAD); // шаг по х
	// первое условие ограничивает дальность прорисовки
	// второе условие проверят попадание луча в стену
	while (mlx->player.x + ray.x < MAX_RANGE && mlx->player.y + ray.y < MAX_RANGE \
	&& check_cube(mlx, mlx->player.x + ray.x, mlx->player.y + ray.y) != 1)
	{
		ray.x += dx;
		ray.y += dy;
	}
	fish_fix = cos((degrees - mlx->degrees) * RAD); // формула из интернета
	ray.ray_len = sqrt(pow(ray.y, 2.0) + pow(ray.x, 2.0)) * fish_fix; // формула из интернета, которая вычисляет длину луча и выравнивает его, что бы избежать рыбий глаз
	return (ray);
}


float	find_cubx(t_vars *mlx, t_rayinfo ray)
{
	float cubx;
	float cuby;

	cubx = (ray.x + mlx->player.x) / TEXTURE_SIZE ; // какой куб по Х по счету
	cuby = (ray.y + mlx->player.y) / TEXTURE_SIZE; // какой куб по У по счету
	// это ебучее условие даже я не понимаю, но это работает
	if ((int)floor(ray.y + 1 + mlx->player.y) / (int)TEXTURE_SIZE == (int)floor(check_border(ray.y, mlx->player.y)) \
	&& (int)floor(ray.y - 1 + mlx->player.y) / (int)TEXTURE_SIZE == (int)floor(check_border(ray.y, mlx->player.y)))
		cubx = cuby;
	return (cubx);
}

t_data	find_texture(t_vars *mlx, t_rayinfo ray)
{
	t_data	texture;
	int		fix_bag;
	static t_data last_texture;

	// N texture
	texture = mlx->texture;
	// S texture
	if (mlx->player.y > ray.y + mlx->player.y)
		texture = mlx->texture1;
	// это ебучее условие даже я не понимаю, но это работает
	if ((int)floor(ray.y - 1 + mlx->player.y) / (int)TEXTURE_SIZE == (int)floor(check_border(ray.y, mlx->player.y)) \
	&& (int)floor(ray.y + 1 + mlx->player.y) / (int)TEXTURE_SIZE == (int)floor(check_border(ray.y, mlx->player.y)))
	{
		// W texture
		texture = mlx->texture2;
		// E texture
		if (mlx->player.x > ray.x + mlx->player.x)
			texture = mlx->texture3;
	}
	// костыль для фикса бага с полоской в текстурах
	fix_bag = (int)((find_cubx(mlx, ray) - floor(find_cubx(mlx, ray))) * (TEXTURE_SIZE));
	// первая и полсденяя часть стены берет прошлую текстуру и накладывает ее
	if (fix_bag == 0 || fix_bag == 511)
		texture = last_texture;
	last_texture = texture;
	return (texture);
}

int	find_color(t_vars *mlx, t_rayinfo ray, float y, int new_wall)
{
	float	cubx;
	int	texture_align;
	t_data texture;
	int	color;
	int pixel_x;
	int pixel_y;

	texture = find_texture(mlx, ray); // расчет нужной текстры
	cubx = find_cubx(mlx, ray); // расчет координаты куба по оси x
	pixel_x = (cubx - floor(cubx)) * (TEXTURE_SIZE);
	pixel_y = (new_wall - y) / new_wall * (WALL_ALIGN);
	color = get_pixel(&texture, pixel_x,  pixel_y);
	return (color);
}

int	find_color2(t_vars *mlx, t_rayinfo ray, float y, int new_wall)
{
	float	cubx;
	int	texture_align;
	t_data texture;
	int	color2;
	int pixel_x;
	int pixel_y;

	texture = find_texture(mlx, ray); // расчет нужной текстры
	cubx = find_cubx(mlx, ray); // расчет координаты куба по оси x
	pixel_x = (cubx - floor(cubx)) * (TEXTURE_SIZE); 
	pixel_y = y / new_wall * (WALL_ALIGN ) + WALL_ALIGN;
	color2 = get_pixel(&texture, pixel_x,  pixel_y); 
	return (color2);
}

float	draw_wall(t_vars *mlx, int new_wall, t_rayinfo ray, int ray_index)
{
	int color;
	int color2;
	float y;

	y  = 0;
	while (y < WIN_H - 500 && y < new_wall)
	{
		color = find_color(mlx, ray, y, new_wall); // расчет пикселя верхней части текстуры
		color2 = find_color2(mlx, ray, y, new_wall); // расчет пискеля нижней части текстуры
		my_mlx_pixel_put(&mlx->img, (ray_index), 500 - y , color);
		my_mlx_pixel_put(&mlx->img, (ray_index),  500 + y, color2);
		++y;
	}
	return (y);
}

void ray_cast(t_rayinfo ray, int ray_index, t_vars *mlx)
{
	float		y;
	int			new_wall;

	new_wall = RATIO_DISPLAY / ray.ray_len; // расчет длины стены
	y = draw_wall(mlx, new_wall, ray, ray_index);
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
	ray_len = 0;
	while (ray_len++ < 1000)
	{
		if (ray_len == 500)
			my_mlx_pixel_put(&mlx->img, 500, 500 , 0x00ff0000);
		ray_cast(print_line(mlx, degrees - 25, mlx->player.x, mlx->player.y), ray_index, mlx);
		ray_index += 1;
		// каждый луч мы отклоняем для, делая полокруг из лучей
		//   /      		
		//  /    _-              
		//|/  _- 
		//|_- 
		//|-- -- -- --
		//|-_ 
		//|\   -_ 
		//  \      -_
		//   \        |
		degrees += 0.05;
	}
}