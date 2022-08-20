/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaryam <fmaryam@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/20 22:40:50 by fmaryam           #+#    #+#             */
/*   Updated: 2022/08/20 22:40:57 by fmaryam          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "index.h"

void	wall_init(t_vars *game)
{
	int	w;
	int	h;

	game->texture.img = mlx_new_image(game->mlx, 512, 512);
	game->texture.img = mlx_xpm_file_to_image(game->mlx, "wall.xpm", &w, &h);
	game->texture.addr = mlx_get_data_addr(game->texture.img, \
	&game->texture.bits_per_pixel, &game->texture.line_length, \
	&game->texture.endian);
	game->texture1.img = mlx_new_image(game->mlx, 512, 512);
	game->texture1.img = mlx_xpm_file_to_image(game->mlx, "wall1.xpm", &w, &h);
	game->texture1.addr = mlx_get_data_addr(game->texture1.img, \
	&game->texture1.bits_per_pixel, &game->texture1.line_length, \
	&game->texture1.endian);
	game->texture2.img = mlx_new_image(game->mlx, 512, 512);
	game->texture2.img = mlx_xpm_file_to_image(game->mlx, "wall2.xpm", &w, &h);
	game->texture2.addr = mlx_get_data_addr(game->texture2.img, \
	&game->texture2.bits_per_pixel, &game->texture2.line_length, \
	&game->texture2.endian);
	game->texture3.img = mlx_new_image(game->mlx, 512, 512);
	game->texture3.img = mlx_xpm_file_to_image(game->mlx, "wall3.xpm", &w, &h);
	game->texture3.addr = mlx_get_data_addr(game->texture3.img, \
	&game->texture3.bits_per_pixel, &game->texture3.line_length, \
	&game->texture3.endian);
}

void	game_init(t_vars *game)
{
	game->sky = 500;
	game->degrees = game->player.degrees;
	game->front = 0;
	game->back = 0;
	game->left = 0;
	game->right = 0;
	game->sprint = 1;
	game->turn_left = 0;
	game->turn_right = 0;
	wall_init(game);
}

void	my_mlx_init(t_vars *game, t_map *map_data)
{
	game->mlx = mlx_init();
	game->mlx_win = mlx_new_window(game->mlx, WIN_W, WIN_H, "Hello world!");
	game->img.img = mlx_new_image(game->mlx, WIN_W, WIN_H);
	game->img.addr = mlx_get_data_addr(game->img.img, \
	&(game->img.bits_per_pixel), &(game->img.line_length), &(game->img.endian));
	game->map_data = map_data;
	game_init(game);
	mlx_hook(game->mlx_win, 2, 1L << 0, key_hook, game);
	mlx_key_hook(game->mlx_win, key_down, game);
	mlx_hook(game->mlx_win, 6, 1L << 0, mouse_hook, game);
	mlx_loop_hook(game->mlx, render_next_frame, game);
	mlx_loop(game->mlx);
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