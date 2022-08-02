#include "index.h"

void	door_init(t_door *doors, int *current, int j, int i)
{
	doors[*current].x = j;
	doors[*current].y = i;
	// something else
	(*current)++;
}

void	coin_init(t_coin *coins, int *current, int j, int i)
{
	coins[*current].x = j;
	coins[*current].y = i;
	// something else
	(*current)++;
}

int	objects_init(t_vars *game, t_list *cleaner)
{
	int	c_count;
	int	d_count;
	int	i;
	t_door	*doors;

	objects_count(game, &c_count, &d_count);
	game->coins_count = c_count;
	game->coins = malloc(sizeof(t_coin) * (c_count));
	if (!game->coins || ft_clslist_add_front(cleaner, game->coins))
		return (1);
	doors = malloc(sizeof(t_door) * (d_count + 1));
	if (!doors)
		return (1);
	fill_coins_doors(game, game->coins, doors);
	add_random(game, game->coins, doors, d_count);
	i = -1;
	while (++i < game->coins_count)
		game->map_data->mmap[game->coins[i].y]->line[game->coins[i].x] = 'C';
	game->map_data->mmap[game->door.y]->line[game->door.x] = game->door.side;
	free(doors);
	return (0);
}

int	player_init(t_player *player, int i, int k, char *side)
{
	if (player->x != -1)
		return (1);
	player->da = 0;
	if (*side == 'N')
		player->degrees = 0;
	if (*side == 'E')
		player->degrees = 90;
	if (*side == 'S')
		player->degrees = 180;
	if (*side == 'W')
		player->degrees = 270;
	*side = '0';
	player->x = i * BLOCK_SIZE;
	player->y = k * BLOCK_SIZE;
	return (0);
}