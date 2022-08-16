/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aconchit <aconchit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 10:57:35 by aconchit          #+#    #+#             */
/*   Updated: 2022/08/15 10:57:36 by aconchit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "index.h"

int	draw_sky(t_vars *mlx, float y, int ray_index)
{
	int	color;

	color = 0x00bfff;
	while (y < WIN_H - mlx->sky)
	{
		my_mlx_pixel_put(&mlx->img, (ray_index), 500 - y, color);
		++y;
	}
	return (0);
}

int	draw_floor(t_vars *mlx, float y, int ray_index)
{
	int	color;

	color = 0x505050;
	while (y < WIN_H - (WIN_H - mlx->sky))
	{
		my_mlx_pixel_put(&mlx->img, (ray_index), 500 + y, color);
		++y;
	}
	return (0);
}
