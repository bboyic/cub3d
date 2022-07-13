#include "index.h"

int	key_hook(int keycode, t_vars *game)
{
	printf("Hello from key_hook %d!\n", keycode);
	// linux
	// if (keycode == 100)
	// 	game->left = 1;
	// if (keycode == 115)
	// 	game->back = 1;
	// if (keycode == 97)
	// 	game->right = 1;
	// if (keycode == 119)
	// 	game->front = 1;
	// if (keycode == 65505)
	// 	game->sprint = 2;
	// if (keycode == 12) // q
	// 	game->turn_left = 1;
	// if (keycode == 14) // e
	// 	game->turn_right = 1;
	// mac
	if (keycode == 0)
		game->left = 1;
	if (keycode == 115)
		game->back = 1;
	if (keycode == 97)
		game->right = 1;
	if (keycode == 119)
		game->front = 1;
	if (keycode == 65505)
		game->sprint = 2;
	if (keycode == 12) // q
		game->turn_left = 1;
	if (keycode == 14) // e
		game->turn_right = 1;
	// mac
	// if (keycode == 0)
	// 	game->left = 1;
	// if (keycode == 1)
	// 	game->back = 1;
	// if (keycode == 2)
	// 	game->right = 1;
	// if (keycode == 13)
	// 	game->front = 1;
	// if (keycode == 257)
	// 	game->sprint = 2;
	// if (keycode == 12)
	// 	game->turn_left = 1;
	// if (keycode == 14)
	// 	game->turn_right = 1;
	return (0);
}

int	key_down(int keycode, t_vars *game)
{
	//printf("Hello from key_hook %d!\n", keycode);
	if (keycode == 0)
		game->left = 0;
	if (keycode == 1)
		game->back = 0;
	if (keycode == 2)
		game->right = 0;
	if (keycode == 13)
		game->front = 0;
	if (keycode == 257)
		game->sprint = 1;
	if (keycode == 12)
		game->turn_left = 0;
	if (keycode == 14)
		game->turn_right = 0;
	return (0);
}