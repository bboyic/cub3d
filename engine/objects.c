#include "index.h"
#include "time.h"

int	c_rand(int spread, int i)
{
	// TODO: think about time generator
	time_t t1;
	srand ( (unsigned) time (&t1) * i);
	// srand((unsigned int)1);
	int a = rand() % spread;
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