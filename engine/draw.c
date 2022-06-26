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
			// тут надо решить, перерисовываем ли мы пиксели под место, зарезервированное под миникарту
			// сделаем наложение, миникарту отрисуем в конце
			// if (check_cube(mlx, x, y))
			// {
			// 	my_mlx_pixel_put(&mlx->img, x, y, 0x000F000F);
			// } 
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