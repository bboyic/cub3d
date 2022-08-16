/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ifs_for_move.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aconchit <aconchit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 11:47:36 by aconchit          #+#    #+#             */
/*   Updated: 2022/08/16 12:28:27 by aconchit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "index.h"

int	front_if(t_vars *mlx)
{
	float	x;
	float	y;
	float	dx;
	float	dy;

	x = mlx->player.x;
	y = mlx->player.y;
	dx = mlx->player.dx;
	dy = mlx->player.dy;
	if (mlx->front == 1 && check_cube(mlx, x + (dx * 2) * mlx->sprint * SPEED, \
	y - (dy * 2) * mlx->sprint * SPEED) != 1)
		return (1);
	return (0);
}

int	back_if(t_vars *mlx)
{
	float	x;
	float	y;
	float	dx;
	float	dy;

	x = mlx->player.x;
	y = mlx->player.y;
	dx = mlx->player.dx;
	dy = mlx->player.dy;
	if (mlx->back == 1 && check_cube(mlx, x - (dx * 2) * mlx->sprint * SPEED, \
	y + (dy * 2) * mlx->sprint * SPEED) != 1)
		return (1);
	return (0);
}

int	left_if(t_vars *mlx)
{
	float	x;
	float	y;
	float	dx;
	float	dy;

	x = mlx->player.x;
	y = mlx->player.y;
	dx = mlx->player.dx;
	dy = mlx->player.dy;
	if (mlx->left == 1 && check_cube(mlx, x - (dy * 2) * mlx->sprint * SPEED, \
	y - (dx * 2) * mlx->sprint * SPEED) != 1)
		return (1);
	return (0);
}

int	right_if(t_vars *mlx)
{
	float	x;
	float	y;
	float	dx;
	float	dy;

	x = mlx->player.x;
	y = mlx->player.y;
	dx = mlx->player.dx;
	dy = mlx->player.dy;
	if (mlx->right == 1 && check_cube(mlx, x + (dy * 2) * mlx->sprint * SPEED, \
	y + (dx * 2) * mlx->sprint * SPEED) != 1)
		return (1);
	return (0);
}

int	angle_fix(t_vars *mlx)
{
	float	x;
	float	y;
	float	dx;
	float	dy;

	x = mlx->player.x;
	y = mlx->player.y;
	dx = mlx->player.dx;
	dy = mlx->player.dy;
	if ((check_cube(mlx, x - (dy * 2) * mlx->sprint * SPEED, \
	y - (dx * 2) * mlx->sprint * SPEED) != 1 \
	&& check_cube(mlx, x + (dy * 5) * mlx->sprint * SPEED, \
	y + (dx * 5) * mlx->sprint * SPEED)) == 1 \
	|| (check_cube(mlx, x - (dy * 2) * mlx->sprint * SPEED, \
	y - (dx * 2) * mlx->sprint * SPEED) == 1 \
	&& check_cube(mlx, x + (dy * 5) * mlx->sprint * SPEED, \
	y + (dx * 5) * mlx->sprint * SPEED)) != 1 \
	|| (check_cube(mlx, x - (dy * 2) * mlx->sprint * SPEED, \
	y - (dx * 2) * mlx->sprint * SPEED) != 1 \
	&& check_cube(mlx, x + (dy * 5) * mlx->sprint * SPEED, \
	y + (dx * 5) * mlx->sprint * SPEED)) != 1)
		return (1);
	return (0);
}
