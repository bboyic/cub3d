/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaryam <fmaryam@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 17:24:31 by aconchit          #+#    #+#             */
/*   Updated: 2022/08/20 22:47:38 by fmaryam          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "index.h"

int	check_cube(t_vars *mlx, int x, int y)
{
	if (y / 512 < mlx->map_data->height \
	&& x / 512 < mlx->map_data->mmap[y / 512]->len \
	&& mlx->map_data->mmap[y / 512]->line[x / 512] == '1')
		return (1);
	else
		return (0);
}

int	render_next_frame(void *data)
{
	t_vars	*game;

	game = (t_vars *)data;
	check_move(game);
	draw_ray(game);
	mlx_put_image_to_window(game->mlx, game->mlx_win, game->img.img, 0, 0);
	return (0);
}

int	main(int ar, char *av[])
{
	t_vars	game;
	t_list	*cleaner;
	t_map	*map_data;

	if (ar != 2)
		return (ft_write(2, "Too many/few arguments\n"));
	cleaner = malloc(sizeof(t_list) * 1);
	if (!cleaner)
		return (ft_write(2, "Error: Allocate cleaner\n"));
	cleaner->key = 0;
	cleaner->next = 0;
	game.player.x = -1;
	game.player.y = -1;
	map_data = ft_map(av[1], &game.player, cleaner);
	if (!map_data)
	{
		ft_cleaner(cleaner);
		return (0);
	}
	game.map_data = map_data;
	game.cleaner = cleaner;
	my_mlx_init(&game, map_data);
	ft_cleaner(cleaner);
	return (0);
}
