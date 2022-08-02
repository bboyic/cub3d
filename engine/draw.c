#include "index.h"

// int	draw_cub(int color, int x, int y)
// {
// 	int x_index;
// 	int	y_index;

// 	y_index = 0;
// 	while (y_index < 40)
// 	{
// 		x_index = 0;
// 		while (x_index < 40)
// 		{
// 			my_mlx_pixel_put(&vars->img, x_index + (x * 40), y_index + (y * 40), color);
// 			++x_index;
// 		}
// 		++y_index;
// 	}
// 	return (0);
// }

// todo: Danya, wtf?
void	draw_background(t_vars *mlx)
{
	int	max_x;
	int	max_y;
	int	x;
	int	y;

	// max_y = 400;
	// max_x = 600;
	y = 0;
	while (y < WIN_H)
	{
		x = 0;
		while (x < WIN_W)
		{
			// тут надо решить, перерисовываем ли мы пиксели под место, зарезервированное под миникарту
			// сделаем наложение, миникарту отрисуем в конце
			// if (check_cube(mlx, x, y))
			// {
			// 	my_mlx_pixel_put(&mlx->img, x, y, 0x000F000F);
			// } 
			// else
			my_mlx_pixel_put(&mlx->img, x, y, 0x00000000);
			++x;
		}
		++y;
	}
}

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