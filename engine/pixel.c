/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aconchit <aconchit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/15 16:25:18 by aconchit          #+#    #+#             */
/*   Updated: 2022/08/15 16:25:47 by aconchit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "index.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

int	get_pixel(t_data *img, int x, int y)
{
	int		*dst;
	int		color;

	dst = (void *)img->addr + (y * img->line_length + x * \
												(img->bits_per_pixel / 8));
	color = *(int *)dst;
	return (color);
}
