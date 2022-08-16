/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aconchit <aconchit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 11:01:55 by aconchit          #+#    #+#             */
/*   Updated: 2022/08/16 12:27:59 by aconchit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "index.h"

void	sample_move(t_vars *mlx)
{
	int	speed;

	speed = 20;
	mlx->player.dy = cos(mlx->degrees * RAD);
	mlx->player.dx = sin(mlx->degrees * RAD);
	if (front_if(mlx) && angle_fix(mlx))
	{
		mlx->player.x += mlx->player.dx * mlx->sprint * SPEED;
		mlx->player.y -= mlx->player.dy * mlx->sprint * SPEED;
	}
	if (back_if(mlx))
	{
		mlx->player.x -= mlx->player.dx * mlx->sprint * SPEED;
		mlx->player.y += mlx->player.dy * mlx->sprint * SPEED;
	}
	if (left_if(mlx))
	{
		mlx->player.x -= mlx->player.dy * mlx->sprint * SPEED;
		mlx->player.y -= mlx->player.dx * mlx->sprint * SPEED;
	}
	if (right_if(mlx))
	{
		mlx->player.x += mlx->player.dy * mlx->sprint * SPEED;
		mlx->player.y += mlx->player.dx * mlx->sprint * SPEED;
	}
}

void	turn_move(t_vars *mlx)
{
	if (mlx->turn_left == 1)
	{
		mlx->degrees -= 2;
		mlx->player.dy = cos(mlx->degrees * RAD);
		mlx->player.dx = sin(mlx->degrees * RAD);
		if (mlx->degrees <= 0)
			mlx->degrees = 360;
	}
	if (mlx->turn_right == 1)
	{
		mlx->degrees += 2;
		mlx->player.dy = cos(mlx->degrees * RAD);
		mlx->player.dx = sin(mlx->degrees * RAD);
		if (mlx->degrees >= 360)
			mlx->degrees = 0;
	}
}

void	check_move(t_vars *mlx)
{
	sample_move(mlx);
	turn_move(mlx);
}
