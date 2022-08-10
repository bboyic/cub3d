#include "index.h"

void	sample_move(t_vars *mlx)
{
	int speed;

	speed = 20;
	if (mlx->front == 1 && check_cube(mlx, mlx->player.x + (mlx->player.dx * 2) * mlx->sprint * speed, mlx->player.y - (mlx->player.dy * 2) * mlx->sprint * speed) != 1)
	{
		if ((check_cube(mlx, mlx->player.x - (mlx->player.dy * 2) * mlx->sprint * speed, mlx->player.y - (mlx->player.dx * 2) * mlx->sprint * speed) != 1 \
		 && check_cube(mlx, mlx->player.x + (mlx->player.dy * 5) * mlx->sprint * speed, mlx->player.y + (mlx->player.dx * 5) * mlx->sprint * speed)) == 1 \
		 || (check_cube(mlx, mlx->player.x - (mlx->player.dy * 2) * mlx->sprint * speed, mlx->player.y - (mlx->player.dx * 2) * mlx->sprint * speed) == 1\
		 && check_cube(mlx, mlx->player.x + (mlx->player.dy * 5) * mlx->sprint * speed, mlx->player.y + (mlx->player.dx * 5) * mlx->sprint * speed)) != 1\
		 || (check_cube(mlx, mlx->player.x - (mlx->player.dy * 2) * mlx->sprint * speed, mlx->player.y - (mlx->player.dx * 2) * mlx->sprint * speed) != 1\
		 && check_cube(mlx, mlx->player.x + (mlx->player.dy * 5) * mlx->sprint * speed, mlx->player.y + (mlx->player.dx * 5) * mlx->sprint * speed)) != 1)
		{
			mlx->player.x += mlx->player.dx * mlx->sprint * speed; 
			mlx->player.y -= mlx->player.dy * mlx->sprint * speed;
		}
	}
	if (mlx->back == 1 && check_cube(mlx, mlx->player.x - (mlx->player.dx * 2) * mlx->sprint * speed, mlx->player.y + (mlx->player.dy * 2) * mlx->sprint * speed) != 1)
	{
	
			mlx->player.x -= mlx->player.dx * mlx->sprint * speed; 
			mlx->player.y += mlx->player.dy * mlx->sprint * speed;
	}
	if (mlx->left == 1 && check_cube(mlx, mlx->player.x - (mlx->player.dy * 2) * mlx->sprint * speed, mlx->player.y - (mlx->player.dx * 2) * mlx->sprint * speed) != 1)
	{
		mlx->player.x -= mlx->player.dy * mlx->sprint * speed;
		mlx->player.y -= mlx->player.dx * mlx->sprint * speed;
	}
	if (mlx->right == 1 && check_cube(mlx, mlx->player.x + (mlx->player.dy * 2) * mlx->sprint * speed, mlx->player.y + (mlx->player.dx * 2) * mlx->sprint * speed) != 1)
	{
		mlx->player.x += mlx->player.dy * mlx->sprint * speed;
		mlx->player.y += mlx->player.dx * mlx->sprint * speed;
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