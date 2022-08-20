/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaryam <fmaryam@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 16:16:27 by aconchit          #+#    #+#             */
/*   Updated: 2022/08/20 22:22:09 by fmaryam          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "index.h"

float	find_cubx(t_vars *mlx, t_rayinfo ray)
{
	float	cubx;
	float	cuby;

	cubx = (ray.x + mlx->player.x) / TEXTURE_SIZE ;
	cuby = (ray.y + mlx->player.y) / TEXTURE_SIZE;
	if (mlx->player.fck_if)
		cubx = cuby;
	return (cubx);
}

t_data	find_texture(t_vars *mlx, t_rayinfo ray)
{
	t_data			texture;
	int				fix_bag;
	static t_data	last_texture;

	texture = mlx->texture;
	if (mlx->player.y > ray.y + mlx->player.y)
		texture = mlx->texture1;
	if (mlx->player.fck_if)
	{
		texture = mlx->texture2;
		if (mlx->player.x > ray.x + mlx->player.x)
			texture = mlx->texture3;
	}
	fix_bag = (int)((find_cubx(mlx, ray) - \
	floor(find_cubx(mlx, ray))) * (TEXTURE_SIZE));
	if (fix_bag == 0 || fix_bag == 511)
		texture = last_texture;
	last_texture = texture;
	return (texture);
}

int	find_color(t_vars *mlx, t_rayinfo ray, float y, int new_wall)
{
	float	cubx;
	t_data	texture;
	int		pixel_x;
	int		pixel_y;

	texture = find_texture(mlx, ray);
	cubx = find_cubx(mlx, ray);
	pixel_x = (cubx - floor(cubx)) * (TEXTURE_SIZE);
	pixel_y = (new_wall - y) / new_wall * (WALL_ALIGN);
	return (get_pixel(&texture, pixel_x, pixel_y));
}

int	find_color2(t_vars *mlx, t_rayinfo ray, float y, int new_wall)
{
	float	cubx;
	t_data	texture;
	int		pixel_x;
	int		pixel_y;

	texture = find_texture(mlx, ray);
	cubx = find_cubx(mlx, ray);
	pixel_x = (cubx - floor(cubx)) * (TEXTURE_SIZE);
	pixel_y = y / new_wall * (WALL_ALIGN) + WALL_ALIGN;
	return (get_pixel(&texture, pixel_x, pixel_y));
}

float	draw_wall(t_vars *mlx, int new_wall, t_rayinfo ray, int ray_index)
{
	int		color;
	int		color2;
	float	y;

	y = 0;
	while (y < WIN_H - 500 && y < new_wall)
	{
		color = find_color(mlx, ray, y, new_wall);
		color2 = find_color2(mlx, ray, y, new_wall);
		my_mlx_pixel_put(&mlx->img, (ray_index), 500 - y, color);
		my_mlx_pixel_put(&mlx->img, (ray_index), 500 + y, color2);
		++y;
	}
	return (y);
}
