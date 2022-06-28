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

void	draw_minimap(t_vars *game)
{
	int	x;
	int	y;
	int	mini_x;
	int	mini_y;

	mini_x = game->player.x - MINI_W / 2;
	mini_y = game->player.y - MINI_H / 2;
	check_scale(game->map_data, mini_x, mini_y);
	y = 0;
	while (y / BLOCK_SIZE < MINI_H)
	{
		x = 0;
		while (x / BLOCK_SIZE < MINI_W)
		{
			if (game->map_data->mmap[mini_y + y / BLOCK_SIZE]->line[
				mini_x + x / BLOCK_SIZE] == '1')
				my_mlx_pixel_put(&game->img, x + mini_x * BLOCK_SIZE,
					y + mini_y * BLOCK_SIZE, 0x000F000F);
			x++;
		}
	}
}