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

#include "index.h"

int	check_cube(t_vars *mlx, int x, int y)
{
	if (y / 16 < 8 && x / 16 < 12 && mlx->map[y / 16][x / 16] == '1')
		return (1);
	else
		return (0);
}

int	render_next_frame(void *data) {
	t_vars *mlx;

	mlx = (t_vars *)data;
	check_move(mlx);
	draw_background(mlx);
	draw_player(mlx);
	draw_ray(mlx);
	mlx_put_image_to_window(mlx->mlx, mlx->mlx_win, mlx->img.img, 0, 0);
	return (0);
}

void	palyer_init(t_vars *game)
{
	game->degrees = 0;
	game->player.da = 0;
	game->player.dy = cos(0);
	game->player.dx = sin(0);
	game->player.x = 150;
	game->player.y = 150;
	game->front = 0;
	game->back = 0;
	game->left = 0;
	game->right = 0;
	game->sprint = 1;
	game->turn_left = 0;
	game->turn_right = 0;
	game->map = 
}

void	my_mlx_init(t_vars *game)
{
	game->mlx = mlx_init();
	game->mlx_win = mlx_new_window(game->mlx, 1000, 300, "Hello world!");
	game->img.img = mlx_new_image(game->mlx, 1000, 300);
	game->img.addr = mlx_get_data_addr(game->img.img, &(game->img.bits_per_pixel), &(game->img.line_length),
								&(game->img.endian));
	palyer_init(game);
	mlx_hook(game->mlx_win, 2, 1L<<0, key_hook, mlx);
	mlx_key_hook(game->mlx_win, key_down, mlx);
	mlx_loop_hook(game->mlx, render_next_frame, mlx);
	mlx_loop(game->mlx);
}

int	main(void) 
{
	t_vars	game;
	t_list *cleaner;

	cleaner = malloc(sizeof(t_list) * 1);
	t_map *map_data = ft_map("beu_map.cub", cleaner);
	if (!map_data)
		return (0);
	printf("%s\n%s\n%s\n%s\n", map_data->texture_of_east, map_data->texture_of_north, map_data->texture_of_south, map_data->texture_of_west);
	printf("floor=%d,%d,%d\n", map_data->rgb_floor[0], map_data->rgb_floor[1], map_data->rgb_floor[2]);
	printf("ceiling=%d,%d,%d\n", map_data->rgb_ceiling[0], map_data->rgb_ceiling[1], map_data->rgb_ceiling[2]);
	int i = 0;
	while (map_data->mmap[i]){
		printf("%s", map_data->mmap[i]->line);
		i++;
	}
	my_mlx_init(&game);
	// printf("hey it is check static param = %d\n", mlx.back);
	return (0);
}
