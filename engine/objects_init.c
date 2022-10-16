/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaryam <fmaryam@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 22:12:44 by fmaryam           #+#    #+#             */
/*   Updated: 2022/10/16 19:45:15 by fmaryam          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "index.h"

void	door_init(t_door *doors, int *current, int j, int i)
{
	doors[*current].x = j;
	doors[*current].y = i;
	doors[*current].real = 0;
	doors[*current].unlock = 0;
	(*current)++;
}

void	coin_init(t_coin *coins, int *current, int j, int i)
{
	coins[*current].x = j;
	coins[*current].y = i;
	coins[*current].is = 1;
	(*current)++;
}

int	objects_init(t_vars *game, t_list *cleaner)
{
	int	i;

	objects_count(game, &game->coins_count, &game->doors_count);
	game->coins = malloc(sizeof(t_coin) * (game->coins_count));
	if (!game->coins || ft_clslist_add_front(cleaner, game->coins))
		return (1);
	game->doors = malloc(sizeof(t_door) * (game->doors_count));
	if (!game->doors || ft_clslist_add_front(cleaner, game->doors))
		return (1);
	fill_coins_doors(game, game->coins, game->doors);
	if (add_random_coins(game, game->coins, cleaner))
		return (1);
	i = -1;
	while (++i < game->coins_count)
		game->map_data->mmap[game->coins[i].y]->line[game->coins[i].x] = 'C';
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
