// #include <stdio.h>
// #include <stdlib.h>

// typedef struct temp {
// 	int	kek;
// 	char	*lol;
// 	int	fuck[3];
// }	t_temp;

// void	change_stat_mas(int (*mas)[])
// {
// 	(*mas)[0] = 2;
// }

// t_temp	*get_temp()
// {
// 	t_temp *temp;

// 	temp = malloc(sizeof(t_temp) * 1);
// 	temp->kek = 5;
// 	temp->lol = malloc(sizeof(char) * 1);
// 	temp->lol[0] = 'a';
// 	temp->fuck[0] = 1;
// 	printf("(1)%d %s %d\n", temp->kek, temp->lol, temp->fuck[0]);
// 	change_stat_mas(&temp->fuck);
// 	printf("(1)%d %s %d\n", temp->kek, temp->lol, temp->fuck[0]);
// 	return (temp);
// }

// void	set_temp(t_temp temp)
// {
// 	printf("(exp)%d %s\n", temp.kek, temp.lol);
// }

// int main()
// {
// 	// int	lol[3];

// 	// lol[0] = 1;
// 	// lol[1] = 2;
// 	// lol[2] = 3;
// 	// printf("%d %d %d\n", lol[0], lol[1], lol[2]);
// 	// char *lol = malloc(sizeof(char) * 3);
// 	// lol[0] = 'a';
// 	// lol[1] = 'b';
// 	// lol[2] = 'c';
// 	// char *kek = lol;
// 	// // free(kek);
// 	// printf("%s", lol);
// 	t_temp *temp = get_temp();
// 	printf("(2)%d %s %d\n", temp->kek, temp->lol, temp->fuck[0]);
	
// 	// t_temp temp;

// 	// temp.kek = 5;
// 	// temp.lol = malloc(sizeof(char) * 1);
// 	// temp.lol[0] = 'a';
// 	// set_temp(temp);
// 	// printf("(1)%d %s\n", temp.kek, temp.lol);
// }

// gcc -I mandatory/includes/ utils/map/*.c utils/*.c temp.c

// #include "index.h"
// #include "mlx.h"

//gcc -I mlx -I mandatory/includes -L mlx temp.c -lmlx -framework OpenGL -framework AppKit utils/*.c utils/map/*.c

// int main()
// {
// 	t_list *cleaner;

// 	cleaner = malloc(sizeof(t_list) * 1);
// 	t_map *map_data = ft_map("beu_map.cub", cleaner);
// 	if (!map_data)
// 		return (0);
// 	printf("%s\n%s\n%s\n%s\n", map_data->texture_of_east, map_data->texture_of_north, map_data->texture_of_south, map_data->texture_of_west);
// 	printf("floor=%d,%d,%d\n", map_data->rgb_floor[0], map_data->rgb_floor[1], map_data->rgb_floor[2]);
// 	printf("ceiling=%d,%d,%d\n", map_data->rgb_ceiling[0], map_data->rgb_ceiling[1], map_data->rgb_ceiling[2]);
// 	int i = 0;
// 	while (map_data->mmap[i]){
// 		printf("%s", map_data->mmap[i]->line);
// 		i++;
// 	}
// 	void *mlx = mlx_init();
// 	void *mlx_win = mlx_new_window(mlx, 1920, 1080, "Hello world!");
	
// 	mlx_loop(mlx);
// }

#include "includes/index.h"

int	check_cube(t_vars *mlx, int x, int y)
{
	if (y / 512 < mlx->map_data->height && x / 512 < mlx->map_data->mmap[y/512]->len && mlx->map_data->mmap[y/512]->line[x/512] == '1')
		return (1);
	else
		return (0);
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

int	render_next_frame(void *data) {
	t_vars *game;

	game = (t_vars *)data;
	check_move(game);

	draw_background(game);
	// draw_player(game);
	draw_ray(game);
	// draw_sky(game);
	// add sprite, measure the time; change sprite and reset time after reaching the value
	mlx_put_image_to_window(game->mlx, game->mlx_win, game->img.img, 0, 0);
	//mlx_put_image_to_window(game->mlx, game->mlx_win, game->texture.img, 0, 0);
	return (0);
}

void	wall_init(t_vars *game)
{
	int	w;
	int	h;

	game->texture.img = mlx_new_image(game->mlx, 512, 512);
	game->texture.img = mlx_xpm_file_to_image(game->mlx, "wall.xpm", &w, &h);
	game->texture.addr = mlx_get_data_addr(game->texture.img, &game->texture.bits_per_pixel, &game->texture.line_length, &game->texture.endian);
	game->texture1.img = mlx_new_image(game->mlx, 512, 512);
	game->texture1.img = mlx_xpm_file_to_image(game->mlx, "wall1.xpm", &w, &h);
	game->texture1.addr = mlx_get_data_addr(game->texture1.img, &game->texture1.bits_per_pixel, &game->texture1.line_length, &game->texture1.endian);
	game->texture2.img = mlx_new_image(game->mlx, 512, 512);
	game->texture2.img = mlx_xpm_file_to_image(game->mlx, "wall2.xpm", &w, &h);
	game->texture2.addr = mlx_get_data_addr(game->texture2.img, &game->texture2.bits_per_pixel, &game->texture2.line_length, &game->texture2.endian);
	game->texture3.img = mlx_new_image(game->mlx, 512, 512);
	game->texture3.img = mlx_xpm_file_to_image(game->mlx, "wall3.xpm", &w, &h);
	game->texture3.addr = mlx_get_data_addr(game->texture3.img, &game->texture3.bits_per_pixel, &game->texture3.line_length, &game->texture3.endian);
}

void	game_init(t_vars *game)
{
	int	w;
	int	h;

	game->sky = 500;// количество неба
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
	game->img.addr = mlx_get_data_addr(game->img.img, &(game->img.bits_per_pixel), &(game->img.line_length),
								&(game->img.endian));
	game->map_data = map_data;
	game_init(game);
	mlx_hook(game->mlx_win, 2, 1L<<0, key_hook, game);
	mlx_key_hook(game->mlx_win, key_down, game);
	mlx_hook(game->mlx_win, 6, 1L<<0, mouse_hook, game);
	mlx_loop_hook(game->mlx, render_next_frame, game);
	mlx_loop(game->mlx);
}

int	main(void)
{
	t_vars	game;
	t_list *cleaner;

	cleaner = malloc(sizeof(t_list) * 1);
	if (!cleaner)
		return (1);
	game.player.x = -1;
	game.player.y = -1;
	t_map *map_data = ft_map("beu_map.cub", &game.player, cleaner); // todo: check leaks
	if (!map_data)
	{
		ft_cleaner(cleaner);
		return (0);
	}
	game.map_data = map_data;
	my_mlx_init(&game, map_data);
	ft_cleaner(cleaner);
	return (0);
}
