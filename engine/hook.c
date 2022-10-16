/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaryam <fmaryam@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 10:59:25 by aconchit          #+#    #+#             */
/*   Updated: 2022/10/16 18:17:41 by fmaryam          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "index.h"

int	key_exit(t_vars *game)
{
	ft_cleaner(game->cleaner);
	printf("Exit with code: %d\n", 0);
	exit(0);
}

int	key_hook(int keycode, t_vars *game)
{
	if (keycode == 53)
		ft_exit(0, game->cleaner);
	if (keycode == 0)
		game->left = 1;
	if (keycode == 1)
		game->back = 1;
	if (keycode == 2)
		game->right = 1;
	if (keycode == 13)
		game->front = 1;
	if (keycode == 257)
		game->sprint = 2;
	if (keycode == 12)
		game->turn_left = 1;
	if (keycode == 14)
		game->turn_right = 1;
	return (0);
}

int	key_down(int keycode, t_vars *game)
{
	if (keycode == 0)
		game->left = 0;
	if (keycode == 1)
		game->back = 0;
	if (keycode == 2)
		game->right = 0;
	if (keycode == 13)
		game->front = 0;
	if (keycode == 257)
		game->sprint = 1;
	if (keycode == 12)
		game->turn_left = 0;
	if (keycode == 14)
		game->turn_right = 0;
	return (0);
}

int	mouse_hook(int x, int y, t_vars *mlx)
{
	static int	mx = 0;

	if (x > 0 && x < 1000 && y > 0 && y < 1000 && x != mx)
	{
		mlx->degrees += (x - mx) / 5;
		mlx->player.dy = cos(mlx->degrees * RAD);
		mlx->player.dx = sin(mlx->degrees * RAD);
		if (mlx->degrees <= 0)
			mlx->degrees = 360;
	}
	if (x < 0)
		mlx->turn_left = 1;
	else if (x > 1000)
		mlx->turn_right = 1;
	else
	{
		mlx->turn_left = 0;
		mlx->turn_right = 0;
	}
	mx = x;
	return (0);
}
