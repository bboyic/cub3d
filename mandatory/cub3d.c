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

void	palyer_init(t_vars *mlx)
{
	mlx->degrees = 0;
	mlx->player.da = 0;
	mlx->player.dy = cos(0);
	mlx->player.dx = sin(0);
	mlx->player.x = 150;
	mlx->player.y = 150;
	mlx->front = 0;
	mlx->back = 0;
	mlx->left = 0;
	mlx->right = 0;
	mlx->sprint = 1;
	mlx->turn_left = 0;
	mlx->turn_right = 0;
	mlx->map[0] = "111111111111";
	mlx->map[1] = "100000000001";
	mlx->map[2] = "100100100001";
	mlx->map[3] = "100100000001";
	mlx->map[4] = "100100100001";
	mlx->map[5] = "100000000001";
	mlx->map[6] = "100010010001";
	mlx->map[7] = "111111111111";
}

void	my_mlx_init(t_vars *mlx)
{
	mlx->mlx = mlx_init();
	mlx->mlx_win = mlx_new_window(mlx->mlx, 1000, 300, "Hello world!");
	mlx->img.img = mlx_new_image(mlx->mlx, 1000, 300);
	mlx->img.addr = mlx_get_data_addr(mlx->img.img, &(mlx->img.bits_per_pixel), &(mlx->img.line_length),
								&(mlx->img.endian));
	palyer_init(mlx);
	mlx_hook(mlx->mlx_win, 2, 1L<<0, key_hook, mlx);
	mlx_key_hook(mlx->mlx_win, key_down, mlx);
	mlx_loop_hook(mlx->mlx, render_next_frame, mlx);
	mlx_loop(mlx->mlx);
}

int	main(void) 
{
	t_vars mlx;
	my_mlx_init(&mlx);
	printf("hey it is check static param = %d\n", mlx.back);
	return (0);
}
