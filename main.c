/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aconchit <aconchit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 06:37:54 by aconchit          #+#    #+#             */
/*   Updated: 2022/02/25 16:41:17 by aconchit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include <unistd.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define PI 3.14159265359
#define RD 0.0174533

typedef struct	s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

typedef struct	s_obj {
	int	x;
	int	y;
}	t_obj;


typedef struct	s_vars {
	t_data	img;
	void	*mlx;
	void	*win;
	char *data;
}	t_vars;

typedef struct	s_player {
	float	x;
	float 	y;
	float 	dx;
	float 	dy;
	float	a;
}	t_player;

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

int	draw_all(t_vars *vars)
{

	int	x;
	int	y;

	x = 0;
	y = 0;
	while (y < 700)
	{
		x = 0;
		while (x < 2000)
		{
			my_mlx_pixel_put(&vars->img, x, y, 0xf8f8f7);
			++x;
		}
		++y;
	}
	//mlx_put_image_to_window(vars->mlx, vars->win, vars->img.img, 0, 0);
	return (0);
}

int	check_touch(int x, int y, t_obj obj)
{
	//printf("%d %d , %d %d\n", x ,y , obj.x, obj.y);
	if (x > obj.x - 5 && x < obj.x + 5 && y > obj.y -5 && y < obj.y + 5)
	{
	//	printf("%d %d , %d %d\n", x ,y , obj.x, obj.y);
		return (1);
	}
	return (0);
}

int	draw_his(int size, t_vars *vars)
{
	int	x;
	int	y;

	y = 479;
	while (y > 340 + size)
	{
		x = 639;
		while (x > 500 + size)
		{
			my_mlx_pixel_put(&vars->img, x, y, 0x00FF0000);
			--x;
		}
		--y;
	}
	//mlx_put_image_to_window(vars->mlx, vars->win, vars->img.img, 0, 0);
	return (0);
}

int	check_border_y(float y, float yindex)
{
	return ((y + yindex) / 64);
}

int	check_border_x(float x, float xindex)
{
	return ((x + xindex) / 64);
}

double	rays(float yindex, float xindex, t_player player, int *map, t_vars *vars)
{
	static int 	index = 0;
	int 	i = 0;
	int j = 0;
	while (map[(check_border_y(player.y, yindex) * 8) + (check_border_y(player.x, xindex) + 1) - 1] != 1)//check_x == check_border_x(x, xindex) && check_y == check_border_y(y, yindex))
	{
		my_mlx_pixel_put(&vars->img, ((player.x) + xindex) , player.y + yindex, 0x00BC00);
		xindex += player.dx;
		yindex += player.dy;
	}
	++index;
	//printf("ray %d: x=%f | y=%f size = %f\n", index, xindex, yindex, sqrt((xindex * xindex) + (yindex * yindex)));
	if (index ==  1280)
		index = 0;
	if (index > 1)
	{
		while (i++ < (15000 / sqrtf((xindex * xindex) + (yindex * yindex))))
		{
			j = 0;
			while (j < 1)
			{
				my_mlx_pixel_put(&vars->img, ( (index / 2) + j) + 1000 , 25 + i, (0x00BC00 + sqrt((xindex * xindex) + (yindex * yindex))));
				j++;
			}
		}
		while (i++ < 1000)
		{
			j = 0;
			while (j < 1)
			{
				my_mlx_pixel_put(&vars->img, ( (index / 2) + j) + 1000 , 25 + i, 0x00BCF0);
				j++;
			}
		}
	}
	// if (index >= 40)
	// {
	// 	while (i++ < (15000 / sqrt((xindex * xindex) + (yindex * yindex))))
	// 		my_mlx_pixel_put(&vars->img, ( index * 5) + 1000 , 100 + i, 0x00BC00);
	// }
	// if (index > 40)
	// {
	// 	while (i++ < 500 - sqrt((xindex * xindex) + (yindex * yindex)))
	// 		my_mlx_pixel_put(&vars->img, ((80 - index) * 5 ) + 1000 , 100 + i, 0x00BCF0);
	// }
	printf("%d\n", index);
	return (sqrt((player.x + xindex * player.x + xindex) + (player.y + yindex + player.y + yindex)));
}


int	player(t_player player, t_vars *vars, int *map)
{
	float	xindex;
	float	yindex;
	int		index;
	float	x = player.x;
	float	y = player.y;


	xindex = 0;
	yindex = 0;

	while (yindex < 10)
	{
		xindex = 0;
		while (xindex < 10)
		{
			my_mlx_pixel_put(&vars->img, (x + xindex), (y + yindex), 0x000F0000);
			++xindex ;
		}
		++yindex;
	}
	xindex = 0;
	yindex = 0;
	index = 0;
	int check_x;
	int	check_y;
	float ra;
	float dist;

	check_x = (player.x + xindex) / 64;
	check_y = (player.y + yindex) / 64;
	xindex = player.dx;
	yindex = player.dy;
	player.x += 5;
	ra = player.a - RD * 40;
	while (index++ < 1280)
	{
		if (ra < 0)
			ra += 2 * PI;
		if (ra > 2 * PI)
			ra -= 2 * PI;
		dist = rays(player.dx, player.dy, player, map, vars);	
		player.dx = cos(ra);
		player.dy = sin(ra);
		ra += RD / 20;
	}
	return (0);
}

int	draw_obj(t_obj obj, t_vars *vars)
{
	my_mlx_pixel_put(&vars->img, obj.x, obj.y, 0x00FF0000);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img.img, 0, 0);
	return (0);
}

int draw_cub(int color, int x, int y, t_vars *vars)
{
	int x_index;
	int	y_index;

	y_index = 0;
	while (y_index < 63)
	{
		x_index = 0;
		while (x_index < 63)
		{
			my_mlx_pixel_put(&vars->img, x_index + (x * 64), y_index + (y * 64), color);
			++x_index;
		}
		++y_index;
	}
	//mlx_put_image_to_window(vars->mlx, vars->win, vars->img.img, 0, 0);
	return (0);
}

int	draw_map(int *map, t_vars *vars)
{
	int x;
	int	y = 0;
	int	index = 0;
	
	while (y < 8)
	{
		x = 0;
		while (x < 8)
		{
			if (map[index] == 1)
				draw_cub(0x76776e, x , y, vars);
			else if (map[index] == 0)
				draw_cub(0xcaccbd, x , y, vars);
			++x;
			index++;
		}
		++y;
	}
	return (0);
}

int	game(int keycode, t_vars *vars)
{
	t_obj 		obj;
	static t_player	pl;

	if (pl.x == 0)
	{
		vars->pl.x = 300;
		vars->pl.y = 300;
		vars->pl.a = 0;
		vars->pl.dx = cos(pl.a);
		vars->pl.dy = sin(pl.a);
	}
	int map[] = 
	{
		1, 1, 1, 1, 1, 1, 1, 1,
		1, 0, 1, 0, 0, 0, 0, 1,
		1, 0, 1, 0, 0, 0, 0, 1,
		1, 0, 1, 1, 0, 0, 0, 1,
		1, 0, 0, 0, 0, 0, 0, 1,
		1, 0, 0, 0, 0, 1, 0, 1,
		1, 0, 0, 0, 0, 0, 0, 1,
		1, 1, 1, 1, 1, 1, 1, 1,
	};
	obj.x = 100;
	obj.y = 100;
	
	draw_all(vars);
	if (keycode == 2 && pl.x < 720)
	{
		pl.a += 0.1;
		if (pl.a > 0)
			pl.a -= 2*PI;
		pl.dx = cos(pl.a);
		pl.dy = sin(pl.a);
	}
	if (keycode == 0 && pl.x < 720)
	{
		pl.a -= 0.1;
		if (pl.a < 0)
			pl.a += 2*PI;
		pl.dx = cos(pl.a);
		pl.dy = sin(pl.a);
	}
	if (keycode == 13 && pl.y < 540)
	{
		pl.x += pl.dx * 5;
		pl.y += pl.dy * 5;
	}
	if (keycode == 1 && pl.y < 540)
	{
		pl.x -= pl.dx * 5;
		pl.y -= pl.dy * 5;
	}
	if (keycode == 12)
	{
		pl.a -= 0.1;
		if (pl.a < 0)
			pl.a += 2*PI;
		pl.dx = cos(pl.a) * 5;
		pl.dy = sin(pl.a) * 5;
	}
	if (keycode == 14)
	{
		pl.a += 0.1;
		if (pl.a > 2*PI)
			pl.a -= 2*PI;
		pl.dx = cos(pl.a);
		pl.dy = sin(pl.a);
	}
	//player(x, y, vars);	
	//printf ("|==%d==\n", map[13]);
	draw_map(map, vars);
	//printf ("|==%d==\n", map[13]);
	player(pl, vars, map);
	//my_mlx_pixel_put(&vars->img, pl.x + pl.dx, pl.y + pl.dy, 0x00FF0000);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img.img, 0, 0);
	vars->data = strdup("hello\n");
	if (keycode == 53)
		exit(0);
	printf("%d\n", keycode);
	return (0);
}

int	main(void)
{
	t_data	img;
	t_vars 	vars;

	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, 2000, 700, "Hello world!");
	img.img = mlx_new_image(vars.mlx, 2000, 700);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
								&img.endian);
	vars.img = img;
	//my_mlx_pixel_put(&vars.img, 5, 5, 0x00FF0000);
	mlx_hook(vars.win, 2, 1L<<0, game, &vars);
	mlx_put_image_to_window(vars.mlx, vars.win, img.img, 0, 0);
	mlx_loop(vars.mlx);
	return (0);
}