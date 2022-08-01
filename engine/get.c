#include "index.h"

void	get_money(t_vars *game)
{
	int	i;

	i = -1;
	while (++i < game->coins_count)
	{
		if (game->coins[i].x == (int)(floor(game->player.x / BLOCK_SIZE))
			&& game->coins[i].y == (int)(floor(game->player.y / BLOCK_SIZE)))
		{
			game->map_data->mmap[game->coins[i].y]->line[game->coins[i].x] = '0';
			game->coins[i].is = 0;
			game->collected++;
		}
	}
}

// void	get_door(t_vars *game)
// {
// 	if (game.door.x == (int)(floor(game->player.x / BLOCK_SIZE))
// 		&& game.door.x == (int)(floor(game->player.x / BLOCK_SIZE))
// }