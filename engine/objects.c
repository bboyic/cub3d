#include "index.h"
#include "time.h"

int	c_rand(int spread, int i)
{
	// TODO: think about time generator
	time_t t1;
	srand ( (unsigned) time (&t1) * i);
	// srand((unsigned int)1);
	int a = rand() % spread;
	printf("rand = %d\n", a);
	return (a);
}

void	add_random(t_vars *game, t_coin *coins, t_door *doors, int d)
{
	int	i;
	int	c_i;
	int	rand;
	int	j;

	i = -1;
	c_i = 0;
	while (++i < game->map_data->height)
	{
		rand = c_rand(game->coins_count, i + 1);
		j = 0;
		while (j <= c_i && (coins[j].x != coins[rand].x
			|| coins[j].y != coins[rand].y))
			j++;
		if (j - 1 == c_i)
			coins[c_i++] = coins[rand];
	}
	if (c_i == 0)
		c_i = 1;
	game->coins_count = c_i;
	game->door = doors[c_rand(d, 1)];
}

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

void	fill_coins_doors(t_vars *game, t_coin *coins, t_door *doors)
{
	int	i;
	int	j;
	int	c_i;
	int	d_i;

	i = -1;
	c_i = 0;
	d_i = 0;
	while (++i < game->map_data->height)
	{
		j = -1;
		while (++j < game->map_data->mmap[i]->len)
		{
			if (game->map_data->mmap[i]->line[j] == '0')
				coin_init(coins, &c_i, j, i);
			if (game->map_data->mmap[i]->line[j] == '1'
				&& watch_dogs_legion(game->map_data->mmap,
					game->map_data->height, i, j))
			{
				doors[d_i].side = watch_dogs_legion(game->map_data->mmap,
					game->map_data->height, i, j);
				door_init(doors, &d_i, j, i);
			}
		}
	}
}

void	objects_count(t_vars *game, int *c, int *d)
{
	int	i;
	int	j;
	int	c_count;
	int	d_count;

	c_count = 0;
	d_count = 0;
	i = -1;
	printf("%d\n", game->map_data->height);
	while (++i < game->map_data->height)
	{
		j = -1;
		while (++j < game->map_data->mmap[i]->len)
		{
			if (game->map_data->mmap[i]->line[j] == '0')
				c_count++;
			if (game->map_data->mmap[i]->line[j] == '1'
				&& watch_dogs_legion(game->map_data->mmap,
					game->map_data->height, i, j))
				d_count++;
		}
	}
	*c = c_count;
	*d = d_count;
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
	// todo: clean doors
	return (0);
}

int	player_init(t_player *player, int i, int k, char side)
{
	printf("i am init player\n");
	if (player->x != -1)
		return (1);
	player->da = 0;
	if (side == 'N')
		player->degrees = 0;
	if (side == 'E')
		player->degrees = 90;
	if (side == 'S')
		player->degrees = 180;
	if (side == 'W')
		player->degrees = 270;
	player->x = i * BLOCK_SIZE;
	player->y = k * BLOCK_SIZE;
	return (0);
	// game->player.x = 2270;
	// game->player.y = 5351;
}