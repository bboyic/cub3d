/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aconchit <aconchit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 16:06:23 by aconchit          #+#    #+#             */
/*   Updated: 2022/08/15 16:22:37 by aconchit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "index.h"

float	check_border(float y, float yindex)
{
	return ((y + yindex) / TEXTURE_SIZE);
}

t_rayinfo	print_line(t_vars *mlx, float degrees, float x, float y)
{
	float		dx;
	float		dy;
	float		fish_fix;
	t_rayinfo	ray;
	int			color;

	ray.x = 2;
	ray.y = -2;
	dy = -cos(degrees * RAD);
	dx = sin(degrees * RAD);
	while (mlx->player.x + ray.x < MAX_RANGE \
	&& mlx->player.y + ray.y < MAX_RANGE \
	&& check_cube(mlx, mlx->player.x + ray.x, mlx->player.y + ray.y) != 1)
	{
		ray.x += dx;
		ray.y += dy;
	}
	fish_fix = cos((degrees - mlx->degrees) * RAD);
	ray.ray_len = sqrt(pow(ray.y, 2.0) + pow(ray.x, 2.0)) * fish_fix;
	return (ray);
}

void	ray_cast(t_rayinfo ray, int ray_index, t_vars *mlx)
{
	float		y;
	int			new_wall;

	mlx->player.fck_if = 0;
	if ((int)floor(ray.y - 1 + mlx->player.y) / (int)TEXTURE_SIZE \
	== (int)floor(check_border(ray.y, mlx->player.y)) \
	&& (int)floor(ray.y + 1 + mlx->player.y) / (int)TEXTURE_SIZE \
	== (int)floor(check_border(ray.y, mlx->player.y)))
		mlx->player.fck_if = 1;
	new_wall = RATIO_DISPLAY / ray.ray_len;
	y = draw_wall(mlx, new_wall, ray, ray_index);
	draw_sky(mlx, y, ray_index);
	draw_floor(mlx, y, ray_index);
}

void	draw_ray(t_vars *mlx)
{
	int		ray_len;
	float	ray_index;
	float	degrees;

	ray_index = 0;
	degrees = mlx->degrees;
	ray_len = 0;
	while (ray_len++ < 1000)
	{
		if (ray_len == 500)
			my_mlx_pixel_put(&mlx->img, 500, 500, 0x00ff0000);
		ray_cast(print_line(mlx, degrees - 25, mlx->player.x, \
		mlx->player.y), ray_index, mlx);
		ray_index += 1;
		degrees += 0.05;
	}
}
