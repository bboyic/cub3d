#include "index.h"

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