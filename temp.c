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


//gcc -Lmlx_linux -lmlx_Linux -I mandatory/includes/ -Imlx_linux -lXext -lX11 -lm -lz utils/map/*.c utils/*.c temp.c
// #include "index.h"
#include "mlx.h"

int main()
{
	// t_list *cleaner;

	// cleaner = malloc(sizeof(t_list) * 1);
	// t_map *map_data = ft_map("beu_map.cub", cleaner);
	// if (!map_data)
	// 	return (0);
	// printf("%s\n%s\n%s\n%s\n", map_data->texture_of_east, map_data->texture_of_north, map_data->texture_of_south, map_data->texture_of_west);
	// printf("floor=%d,%d,%d\n", map_data->rgb_floor[0], map_data->rgb_floor[1], map_data->rgb_floor[2]);
	// printf("ceiling=%d,%d,%d\n", map_data->rgb_ceiling[0], map_data->rgb_ceiling[1], map_data->rgb_ceiling[2]);
	// int i = 0;
	// while (map_data->mmap[i]){
	// 	printf("%s", map_data->mmap[i]->line);
	// 	i++;
	// }
	void *mlx = mlx_init();
	void *mlx_win = mlx_new_window(mlx, 600, 404, "Hello world!");
	mlx_loop(mlx);
	// printf("not lol\n");
	// print_lol();
}
