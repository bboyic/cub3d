/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aconchit <aconchit@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 16:32:01 by aconchit          #+#    #+#             */
/*   Updated: 2022/02/27 18:02:09 by aconchit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

int			get_pixel(t_data *img, int x, int y)
{
	int		*dst;
	int		color;

	dst = (void *)img->addr + (y * img->line_length + x * \
												(img->bits_per_pixel / 8));
	color = *(int*)dst;
	return (color);
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
		while (x < 800)
		{
			my_mlx_pixel_put(&vars->img, x, y, 0xf8f8f7);
			++x;
		}
		++y;
	}
	return (0);
}

int	check_touch(int x, int y, t_obj obj)
{
	if (x > obj.x - 5 && x < obj.x + 5 && y > obj.y -5 && y < obj.y + 5)
		return (1);
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
	return (0);
}

int	check_border_y(float y, float yindex)
{
	return ((y + yindex) / 40);
}

int	check_border_x(float x, float xindex)
{
	return ((x + xindex) / 40);
}

float	fcheck_border_y(float y, float yindex)
{
	return ((y + yindex) / 40.0);
}

float	fcheck_border_x(float x, float xindex)
{
	return ((x + xindex) / 40.0);
}

double	rays(float yindex, float xindex, t_player player, int *map, t_vars *vars)
{
	static int 	index = 0;
	// float		coastx;
	// float		coasty;
	float		lineH;
	int			color;
	float			cubx;
	float			cuby;
	int			y;
	int			x;
	int			watch;
	// int w;
	// int h;
	float		ca;
	int 	i = 0;
	int j = 0;
	while (map[(check_border_y(player.y, yindex) * 8) + (check_border_y(player.x, xindex) + 1) - 1] != 1)
	{
		my_mlx_pixel_put(&vars->img, ((player.x) + xindex) , player.y + yindex, 0x00BC00);
		xindex += player.dx;
		yindex += player.dy;
	}
	// coastx = xindex;
	// coasty = yindex;
	// while (playercoastx < 320 && coastx > 0 && coasty > 0 && coasty < 320)
	// {
	// 	coastx += player.dx;
	// 	coasty += player.dy;
	// }
	cubx = fcheck_border_y(player.x, xindex);
	cuby = fcheck_border_y(player.y, yindex);
	if (floor(fcheck_border_y(player.x, xindex - player.dx)) != floor(cubx))
	 	cubx = cuby;
	//printf("%d\n", index);
	//++index;
	if (index == 512)
		index = 0;

	ca = player.a - player.ra;
	if (ca < 0)
		ca += 2 * PI;
	if (ca > 2 * PI)
		ca -= 2 * PI;
	// data.img = mlx_xpm_file_to_image(vars->mlx, "wall.xpm", &w, &h);
	// data.addr = mlx_get_data_addr(&data.img, &data.bits_per_pixel, &data.line_length, &data.endian);
	lineH = (30000 / (sqrtf((xindex * xindex) + (yindex * yindex)) * cos(ca)));
	// if (index == 256)
	// 	printf("%f %f\n", floor(fcheck_border_y(player.x, xindex - player.dx)) , floor(cubx));
	while (i++ < vars->pl.z - lineH / 2 && i < 700)
	{
		j = 0;
		while (j < 5)
		{
			//printf("==%d==\n", i);
			my_mlx_pixel_put(&vars->img, ( (index / 2) + j) + (index) , 25 + i, (0x87ceeb));
			j++;
		}
	}
	// if (index == 256)
	// 	printf("%f %f\n", player.x + xindex, player.y + yindex);
	y = 0;
	//printf("%d\n", vars->pl.z);
	x = 0;
	watch = 0;
	if (vars->pl.z - lineH / 2 < 0)
		watch -= vars->pl.z - lineH / 2;
	if (index > 0)
	{
		while (i++ < lineH + (vars->pl.z - lineH / 2) && i < 700)
		{
			j = 0;

			while (j < 2)
			{
				while (x == 512)
					x -= 512;
				//printf("==%d==\n", i);
				//vars->img.img =  mlx_xpm_file_to_image(vars->mlx, "wall.xpm", &w, &h);
				color = 0x00ff00;
				// if (y > 50)
				// 	y = 1;
				color = get_pixel(&vars->textute, (cubx - floor(cubx)) * 512, (y + watch) / ((lineH) / 512));
				// if (index == 256)
				// 	color = 0x00ff00;
				// if (cubx >= 57.0 && cubx < 58.0)
				// 	color = 0x0000ff00;
				// if (cubx == 4.0 && cubx < 5.0)
				// 	color = 0x0000f000;
				// if (cubx == 5.0 && cubx < 6.0)
				// 	color = 0x00000f00;
				my_mlx_pixel_put(&vars->img, ( (index / 2) + j) + (index) , 25 + i, color);
				j++;
				x += floor(xindex) * 512;
			}
			++y;
		}
		while (i++ < 700)
		{
			j = 0;
			while (j < 5)
			{
				my_mlx_pixel_put(&vars->img, ( (index / 2) + j) + (index)  , 25 + i, 0x95A1AB);
				j++;
			}
		}
	}
	++index;
	//printf("%d\n", index);
	return (sqrt((player.x + xindex * player.x + xindex) + (player.y + yindex + player.y + yindex)));
}


// int	player(t_player player, t_vars *vars, int *map)
// {
// 	float	xindex;
// 	float	yindex;
// 	int		index;
// 	float	x = player.x;
// 	float	y = player.y;


// 	xindex = 0;
// 	yindex = 0;

// 	while (yindex < 10)
// 	{
// 		xindex = 0;
// 		while (xindex < 10)
// 		{
// 			my_mlx_pixel_put(&vars->img, (x + xindex), (y + yindex), 0x000F0000);
// 			++xindex ;
// 		}
// 		++yindex;
// 	}
// 	xindex = 0;
// 	yindex = 0;
// 	index = 0;
// 	int check_x;
// 	int	check_y;
// 	//float ra;
// 	float dist;

// 	check_x = (player.x + xindex) / 64;
// 	check_y = (player.y + yindex) / 64;
// 	xindex = player.dx;
// 	yindex = player.dy;
// 	player.x += 5;
// 	player.ra = player.a - RD * 40;
// 	draw_map(map, vars);
// 	while (index++ < 500)
// 	{
// 		if (player.ra < 0)
// 			player.ra += 2 * PI;
// 		if (player.ra > 2 * PI)
// 			player.ra -= 2 * PI;
// 		dist = rays(player.dx, player.dy, player, map, vars);	
// 		player.dx = cos(player.ra);
// 		player.dy = sin(player.ra);
// 		player.ra += RD / 10;
// 	}
// 	return (0);
// }

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
	while (y_index < 40)
	{
		x_index = 0;
		while (x_index < 40)
		{
			my_mlx_pixel_put(&vars->img, x_index + (x * 40), y_index + (y * 40), color);
			++x_index;
		}
		++y_index;
	}
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

void	draw_hands(t_vars *vars)
{
	int	x;
	int	y;
	int	color;

	y = 0;
	while (y < 255)
	{
		x = 0;
		while (x < 350)
		{
			color = get_pixel(&vars->hands, x * 2, y * 2);
			//printf("==color %i==\n", color);
			if (color > 0)
				my_mlx_pixel_put(&vars->img, x + 400, y + 450, color);
			++x;
		}
		++y;
	}
	y = 0;

	while (y < 14)
	{
		x = 0;
		while (x++ < 2)
			my_mlx_pixel_put(&vars->img, x + 375, y + 350, 0x0);
		++y;
	}
	x = 0;
	while (x < 14)
	{
		y = 0;
		while (y++ < 2)
			my_mlx_pixel_put(&vars->img, x + 370, y + 355, 0x0);
		++x;
	}
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
			//my_mlx_pixel_put(&vars->img, (x + xindex), (y + yindex), 0x000F0000);
			++xindex ;
		}
		++yindex;
	}
	xindex = 0;
	yindex = 0;
	index = 0;
	int check_x;
	int	check_y;
	//float ra;
	float dist;

	check_x = (player.x + xindex) / 64;
	check_y = (player.y + yindex) / 64;
	xindex = player.dx;
	yindex = player.dy;
	player.x += 5;
	player.ra = player.a - RD * 40;
	while (index++ < 512)
	{
		if (player.ra < 0)
			player.ra += 2 * PI;
		if (player.ra > 2 * PI)
			player.ra -= 2 * PI;
		dist = rays(player.dx, player.dy, player, map, vars);	
		player.dx = cos(player.ra);
		player.dy = sin(player.ra);
		player.ra += RD / 10;
	}
	yindex = 0;
	draw_map(map, vars);
	draw_hands(vars);
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
	return (0);
}

void	button(t_vars *vars, int keycode, int *map)
{
	if (keycode == 2 && vars->pl.x < 720)
	{
		vars->pl.a += 0.1;
		if (vars->pl.a > 0)
			vars->pl.a -= 2*PI;
		vars->pl.dx = cos(vars->pl.a);
		vars->pl.dy = sin(vars->pl.a);
	}
	if (keycode == 0 && vars->pl.x < 720)
	{
		vars->pl.a -= 0.1;
		if (vars->pl.a < 0)
			vars->pl.a += 2*PI;
		vars->pl.dx = cos(vars->pl.a);
		vars->pl.dy = sin(vars->pl.a);
	}
	if (keycode == 13 && vars->pl.y < 540)
	{
		vars->pl.x += vars->pl.dx * 5;
		vars->pl.y += vars->pl.dy * 5;
		if (map[(check_border_y(vars->pl.y, 10) * 8) + (check_border_y(vars->pl.x, 10) + 1) - 1] == 1)
		{
			vars->pl.x -= vars->pl.dx * 5;
			vars->pl.y -= vars->pl.dy * 5;
		}
	}
	if (keycode == 1 && vars->pl.y < 540)
	{
		vars->pl.x -= vars->pl.dx * 5;
		vars->pl.y -= vars->pl.dy * 5;
		if (map[(check_border_y(vars->pl.y, 10) * 8) + (check_border_y(vars->pl.x, 10) + 1) - 1] == 1)
		{
			vars->pl.x += vars->pl.dx * 5;
			vars->pl.y += vars->pl.dy * 5;
		}
	}
	if (keycode == 12)
	{
		vars->pl.a -= 0.1;
		if (vars->pl.a < 0)
			vars->pl.a += 2*PI;
		vars->pl.dx = cos(vars->pl.a) * 5;
		vars->pl.dy = sin(vars->pl.a) * 5;
	}
	if (keycode == 14)
	{
		vars->pl.a += 0.1;
		if (vars->pl.a > 2*PI)
			vars->pl.a -= 2*PI;
		vars->pl.dx = cos(vars->pl.a);
		vars->pl.dy = sin(vars->pl.a);
	}
}

int	game(int keycode, t_vars *vars)
{
	t_obj 		obj;
	// int w;
	// int h;
	// void	*img;

	//printf("%d\n", data.line_length);
	if (vars->pl.x == 0)
	{
		vars->pl.x = 50;
		vars->pl.y = 50;
		vars->pl.a = 0;
		vars->pl.dx = cos(vars->pl.a);
		vars->pl.dy = sin(vars->pl.a);
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
	//void *img;
	draw_all(vars);
	button(vars, keycode, map);
	//vars->img.img = mlx_xpm_file_to_image(vars->mlx, "wall.xpm", &obj.x, &obj.y);
	//mlx_put_image_to_window(vars->mlx, vars->win, , 0, 0);
	player(vars->pl, vars, map);
	//draw_map(map, vars);
	// while ()
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img.img, 0, 0);
	// img = mlx_xpm_file_to_image(vars->mlx, "hands.xpm", &w, &h);
	//mlx_put_image_to_window(vars->mlx, vars->win, img, 0, 0);
	if (keycode == 53)
		exit(0);
	//printf("%d\n", keycode);
	return (0);
}

void	m_button(t_vars *vars, int x, int y)
{
	static int sx;
	static int sy;

	if (sx == 0)
		sx = x;
	if (sy == 0)
		sy = y;
	if (x > sx + 10 && vars->pl.x < 720)
	{
		vars->pl.a += 0.1;
		if (vars->pl.a > 0)
			vars->pl.a -= 2*PI;
		vars->pl.dx = cos(vars->pl.a);
		vars->pl.dy = sin(vars->pl.a);
		sx = x;
	}
	if (x < sx - 10 && vars->pl.x < 720)
	{
		vars->pl.a -= 0.1;
		if (vars->pl.a < 0)
			vars->pl.a += 2*PI;
		vars->pl.dx = cos(vars->pl.a);
		vars->pl.dy = sin(vars->pl.a);
		sx = x;
	}
	if (y > sy + 5 && vars->pl.y < 540)
	{
		vars->pl.z -= 10;
		sy = y;
	}
	if (y < sy - 5 && vars->pl.y < 540)
	{
		vars->pl.z += 10;
		sy = y;
	}
	// if (keycode == 13 && vars->pl.y < 540)
	// {
	// 	vars->pl.x += vars->pl.dx * 5;
	// 	vars->pl.y += vars->pl.dy * 5;
	// }
	// if (keycode == 1 && vars->pl.y < 540)
	// {
	// 	vars->pl.x -= vars->pl.dx * 5;
	// 	vars->pl.y -= vars->pl.dy * 5;
	// }
	// if (keycode == 12)
	// {
	// 	vars->pl.a -= 0.1;
	// 	if (vars->pl.a < 0)
	// 		vars->pl.a += 2*PI;
	// 	vars->pl.dx = cos(vars->pl.a) * 5;
	// 	vars->pl.dy = sin(vars->pl.a) * 5;
	// }
	// if (keycode == 14)
	// {
	// 	vars->pl.a += 0.1;
	// 	if (vars->pl.a > 2*PI)
	// 		vars->pl.a -= 2*PI;
	// 	vars->pl.dx = cos(vars->pl.a);
	// 	vars->pl.dy = sin(vars->pl.a);
	// }
}

int	m_game(int x, int y, t_vars *vars)
{
	t_obj 		obj;

	if (x < 0 || x > 840 || y < 0 || y > 700)
		return (0);
	if (vars->pl.x == 0)
	{
		vars->pl.x = 50;
		vars->pl.y = 50;
		vars->pl.a = 0;
		vars->pl.dx = cos(vars->pl.a);
		vars->pl.dy = sin(vars->pl.a);
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
	m_button(vars, x, y);
	player(vars->pl, vars, map);
	//draw_map(map, vars);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img.img, 0, 0);
	return (0);
}

// int	render_next_frame(void *data)
// {
// 	t_vars	*vars;
// 	static int		index;

// 	index++;
// 	vars = (t_vars *)data;
// 	if (vars.)
// }

int	main(void)
{
	t_data	img;
	t_vars 	vars;
	int		w;
	int		h;

	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, 800, 700, "Hello world!");
	img.img = mlx_new_image(vars.mlx, 800, 700);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
								&img.endian);
	vars.textute.img = mlx_xpm_file_to_image(vars.mlx, "wall.xpm", &w, &h);
	vars.textute.addr = mlx_get_data_addr(vars.textute.img, &vars.textute.bits_per_pixel, &vars.textute.line_length, &vars.textute.endian);
	vars.hands.img = mlx_xpm_file_to_image(vars.mlx, "hands.xpm", &w, &h);
	vars.hands.addr = mlx_get_data_addr(vars.hands.img, &vars.hands.bits_per_pixel, &vars.hands.line_length, &vars.hands.endian);
	vars.img = img;
	vars.pl.x = 0;
	vars.pl.z = 160;
	mlx_hook(vars.win, 2, 1L<<0, game, &vars);
	mlx_hook(vars.win, 6, 1L<<0, m_game, &vars);

	//mlx_loop_hook(vars.mlx, render_next_frame, &vars);
	mlx_put_image_to_window(vars.mlx, vars.win, img.img, 0, 0);
	mlx_loop(vars.mlx);
	return (0);
}