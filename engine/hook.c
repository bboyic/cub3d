#include "index.h"

int	key_hook(int keycode, t_vars *mlx)
{
	//printf("Hello from key_hook %d!\n", keycode);
	if (keycode == 0)
		mlx->left = 1;
	if (keycode == 1)
		mlx->back = 1;
	if (keycode == 2)
		mlx->right = 1;
	if (keycode == 13)
		mlx->front = 1;
	if (keycode == 257)
		mlx->sprint = 2;
	if (keycode == 12)
		mlx->turn_left = 1;
	if (keycode == 14)
		mlx->turn_right = 1;
	return (0);
}

int	key_down(int keycode, t_vars *mlx)
{
	//printf("Hello from key_hook %d!\n", keycode);
	if (keycode == 0)
		mlx->left = 0;
	if (keycode == 1)
		mlx->back = 0;
	if (keycode == 2)
		mlx->right = 0;
	if (keycode == 13)
		mlx->front = 0;
	if (keycode == 257)
		mlx->sprint = 1;
	if (keycode == 12)
		mlx->turn_left = 0;
	if (keycode == 14)
		mlx->turn_right = 0;
	return (0);
}