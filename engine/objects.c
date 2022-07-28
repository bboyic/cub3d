#include "index.h"

unsigned rand()
{
	unsigned short lfsr = 0xACE1u;
	unsigned bit;

	bit  = ((lfsr >> 0) ^ (lfsr >> 2) ^ (lfsr >> 3) ^ (lfsr >> 5) ) & 1;
	return lfsr =  (lfsr >> 1) | (bit << 15);
}

int	get_door(t_map *map_data, int i, int j)
{
	if ()
}

void	objects_init(t_vars *game) {
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
			if (game->map_data->mmap[i]->line[j] == "0"
				&& rand() > 2)
				game->map_data->mmap[i]->line[j] = "C";
			if (game->map_data->mmap[i]->line[j] == "1" && !door
				&& rand() > 4 && set_door(game->map_data->mmap, i, j))
				door++;
		}
	}
}