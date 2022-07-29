#include "index.h"

int	c_rand(int in)
{
	srand((unsigned int)in);
	int a = rand() % 30;
	printf("%d\n", a);
	return (a);
}

void	objects_init(t_vars *game)
{
	int	i;
	int	j;
	int	door;

	i = -1;
	door = 0;
	while (++i < game->map_data->height)
	{
		j = -1;
		while (++j < game->map_data->mmap[i]->len)
		{
			if (game->map_data->mmap[i]->line[j] == '0'
				&& (c_rand(game->map_data->height * i + j) == 3))
				game->map_data->mmap[i]->line[j] = 'C';
			if (game->map_data->mmap[i]->line[j] == '1' && !door
				&& !(c_rand(game->map_data->height + j * i) % 5) && watch_dogs_legion(game->map_data->mmap,
					game->map_data->height, i, j))
				door++;
		}
	}
}