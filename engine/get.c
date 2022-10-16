/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaryam <fmaryam@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 10:57:58 by aconchit          #+#    #+#             */
/*   Updated: 2022/10/16 18:53:36 by fmaryam          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "index.h"

void	get_money(t_vars *game)
{
	int	i;

	i = -1;
	while (++i < game->coins_count)
	{
		if (game->coins[i].x == (int)(floor(game->player.x / BLOCK_SIZE))
			&& game->coins[i].y == (int)(floor(game->player.y / BLOCK_SIZE))
			&& game->coins[i].is == 1)
		{
			game->map_data->mmap[game->coins[i].y]->line[game->coins[i].x]
				= '0';
			game->coins[i].is = 0;
			game->collected++;
		}
	}
}
