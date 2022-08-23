/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaryam <fmaryam@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 22:12:22 by fmaryam           #+#    #+#             */
/*   Updated: 2022/08/23 22:12:23 by fmaryam          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "index.h"
#include "time.h"

int	c_rand(int spread, int i, t_list *cleaner)
{
	int	*rand;
	int	a;

	rand = malloc(sizeof(int) * 1);
	if (!rand || ft_clslist_add_front(cleaner, rand))
	{
		ft_write(2, "Error: Allocate rand\n");
		return (-1);
	}
	a = (long long)rand % spread;
	return (a);
}

int	add_random_coins(t_vars *game, t_coin *coins, t_list *cleaner)
{
	int	i;
	int	c_i;
	int	rand;
	int	j;

	i = -1;
	c_i = 0;
	while (++i < game->map_data->height)
	{
		rand = c_rand(game->coins_count, i + 1, cleaner);
		if (rand == -1)
			return (1);
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
	return (0);
}

int	add_random_doors(t_vars *game, t_door *doors, t_list *cleaner)
{
	int	i;
	int	d_i;
	int	rand;
	int	j;

	i = -1;
	d_i = 0;
	while (++i < game->map_data->height)
	{
		rand = c_rand(game->doors_count, i + 1, cleaner);
		if (rand == -1)
			return (1);
		j = 0;
		while (j <= d_i && (doors[j].x != doors[rand].x
				|| doors[j].y != doors[rand].y))
			j++;
		if (j - 1 == d_i)
			doors[d_i++] = doors[rand];
	}
	if (d_i == 0)
		d_i = 1;
	game->doors_count = d_i;
	return (0);
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
