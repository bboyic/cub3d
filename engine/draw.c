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

void	draw_in_cub(t_vars *game, int mini_x, int mini_y, int color)
{
	int	x;
	int	y;

	y = 0;
	while (y < MINI_BLOCK_SIZE)
	{
		x = 0;
		while (x < MINI_BLOCK_SIZE)
		{
			// printf("%d %d\n", x + mini_x * MINI_BLOCK_SIZE, y + mini_y * MINI_BLOCK_SIZE);
			if (x > MINI_BLOCK_SIZE / 2 - 5 && x < MINI_BLOCK_SIZE / 2 + 5
			 && y > MINI_BLOCK_SIZE / 2 - 5 && y < MINI_BLOCK_SIZE / 2 + 5)
				my_mlx_pixel_put(&game->img, x + mini_x * MINI_BLOCK_SIZE,
						y + mini_y * MINI_BLOCK_SIZE, color);
			x++;
		}
		y++;
	}
}

void	draw_mini_cub(t_vars *game, int mini_x, int mini_y, int color)
{
	int	x;
	int	y;

	y = 0;
	while (y < MINI_BLOCK_SIZE)
	{
		x = 0;
		while (x < MINI_BLOCK_SIZE)
		{
			// printf("%d %d\n", x + mini_x * MINI_BLOCK_SIZE, y + mini_y * MINI_BLOCK_SIZE);
			my_mlx_pixel_put(&game->img, x + mini_x * MINI_BLOCK_SIZE,
					y + mini_y * MINI_BLOCK_SIZE, color);
			x++;
		}
		y++;
	}
}

void	draw_minimap(t_vars *game)
{
	int	x;
	int	y;
	float	mini_x;
	float	mini_y;

	mini_x = game->player.x / BLOCK_SIZE - MINI_W / 2; // get start position minimap (cut block map for draw)
	mini_y = game->player.y / BLOCK_SIZE - MINI_H / 2;
	y = 0;
	while (y < MINI_H)
	{
		x = 0;
		while (x < MINI_W)
		{
			if ((int)floor(mini_y) + y < 0 || (int)floor(mini_x) + x < 0 ||
				(int)floor(mini_y) + y >= game->map_data->height ||
				(int)floor(mini_x) + x >= game->map_data->mmap[(int)floor(mini_y) + y]->len ||
				game->map_data->mmap[(int)floor(mini_y) + y]->line[(int)floor(mini_x) + x] == ' ')
				x = x;
			else if (game->map_data->mmap[(int)floor(mini_y) + y]->line[(int)floor(mini_x) + x] == '1')
				draw_mini_cub(game, x, y, 0x00696969);
			else if (game->map_data->mmap[(int)floor(mini_y) + y]->line[(int)floor(mini_x) + x] == '0')
				draw_mini_cub(game, x, y, 0x00008B8B);
			else if (game->map_data->mmap[(int)floor(mini_y) + y]->line[(int)floor(mini_x) + x] == 'C')
			{
				draw_mini_cub(game, x, y, 0x00008B8B);
				draw_in_cub(game, x, y, 0x00FFDB58);
			}
			if (mini_x + x == game->player.x / BLOCK_SIZE && mini_y + y == game->player.y / BLOCK_SIZE)
				draw_in_cub(game, x, y, 0x000FF00F);
			x++;
		}
		y++;
	}
}