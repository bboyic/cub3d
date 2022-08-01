#include "index.h"

int	check_cube(t_vars *mlx, int x, int y)
{
	if (y / 512 < mlx->map_data->height && x / 512 < mlx->map_data->mmap[y/512]->len && mlx->map_data->mmap[y/512]->line[x/512] == '1')
		return (1);
	else
		return (0);
}

int	render_next_frame(void *data) {
	t_vars *game;

	game = (t_vars *)data;
	check_move(game);
	draw_background(game);
	draw_ray(game);
	draw_minimap(game);
	mlx_put_image_to_window(game->mlx, game->mlx_win, game->img.img, 0, 0);
	//mlx_put_image_to_window(game->mlx, game->mlx_win, game->texture.img, 0, 0);
	return (0);
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
	game->texture.img = mlx_new_image(game->mlx, 512, 512);
	game->texture.img = mlx_xpm_file_to_image(game->mlx, "wall.xpm", &w, &h);
	game->texture.addr = mlx_get_data_addr(game->texture.img, &game->texture.bits_per_pixel, &game->texture.line_length, &game->texture.endian);
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
	if (!map_data) // TODO:add clean before return
		return (0);
	game.map_data = map_data;
	// printf("i am before objects\n");
	if (objects_init(&game, cleaner))
		return (1); // TODO:add clean before return
	my_mlx_init(&game, map_data);
	return (0);
}
