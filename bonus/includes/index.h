#ifndef MAIN_BONUS_H
# define	MAIN_BONUS_H

#include <unistd.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cub3d_bonus.h"
#include "mlx.h"
#include "get_next_line.h"
#define PI 3.14159265359
#define RAD 0.0174533
#define START_MAP_X 0
#define START_MAP_Y 0
#define BLOCK_SIZE 512
#define MINI_BLOCK_SIZE 30
#define MINI_H 6
#define MINI_W 6
#define WIN_H 1000
#define WIN_W 1000
#define BONUS 11

// undefined
# include <fcntl.h>

/*
* cleaner.c
*/
int		ft_clslist_add_front(t_list *cleaner, void *param);
t_list	*ft_new_clsnode(void *param);
void	ft_cleaner(t_list *cleaner);
void	ft_free_mas(char **mas);

/*
* string.c
*/
int		ft_write(int fd, char *message);
int		ft_white(char *line);
int		watch_dogs(char **file_data, int k, int i);
int		watch_dogs_legion(t_dict **mmap, int height, int k, int i);

/*
* string_utils.c
*/
int		ft_skip_white(char *line);
int		ft_strcmp(char *str1, char *str2);
int		ft_strncmp(char *str1, char *str2, int n);
int		ft_strlen(const char *s);
int		ft_pos_strchr(const char *s, int c);

/*
* split.c
*/
char	**ft_split(char const *s, char c);

/*
* map.c
*/
t_map	*ft_map(char *file, t_player *player, t_list *cleaner);
int		ft_read_file(t_map *map_data, char *file, char ***file_data);
int		ft_get_file_height(char *file, int *height);
int		ft_try_open(char *file, int *fd);
int		ft_convert_rgb_num(const char *str);

/*
* parse.c
*/
int	ft_get_texture(char **texture, char *line, t_list *cleaner, int *fl);
int	ft_get_rgb(int	(*rgb_int)[], char *line, int *fl);
int	ft_get_config(t_map *map_data, char **file_data, t_list *cleaner);
int	ft_copy_into_mmap(t_map *map_data, char **file_data, t_list *cleaner, int i);
int	ft_get_mmap(t_map *map_data, char **file_data, t_player *player, t_list *cleaner);

/*
* valid.c
*/
int	ft_valid_file(char *file);
int	ft_check_name(t_map *map_data, char *line, t_list *cleaner);
int	ft_rgb_size(char **rgb_char);
int	ft_border_line(char *line);
int	ft_inside_line(char **file_data, char *line, int k, t_player *player);

/*
* minimap.c
*/
void	draw_in_cub(t_vars *game, int mini_x, int mini_y, int color);
void	draw_minimap(t_vars *game);
void	draw_mini_cub(t_vars *game, int mini_x, int mini_y, int color);
void	draw_mini_block(t_vars *game, int x, int y);

/*
* draw.c
*/
void	draw_background(t_vars *mlx);
int		draw_sky(t_vars *mlx, float y, int ray_index);
int		draw_floor(t_vars *mlx, float y, int ray_index);

/*
* move.c
*/
void	sample_move(t_vars *mlx);
void	turn_move(t_vars *mlx);
void	check_move(t_vars *mlx);

/*
* raycast.c
*/
t_rayinfo	print_line(t_vars *mlx, float degrees, float x, float y) ;
void		ray_cast(t_rayinfo ray_len, int ray_index, t_vars *mlx);
void		draw_ray(t_vars *mlx);

/*
* pixel.c
*/
void		my_mlx_pixel_put(t_data *data, int x, int y, int color);
int			get_pixel(t_data *img, int x, int y);

/*
* hook.c
*/
int	key_hook(int keycode, t_vars *mlx);
int	key_down(int keycode, t_vars *mlx);
int	mouse_hook(int x, int y, t_vars *mlx);

int	check_cube(t_vars *mlx, int x, int y);

/*
* get.c
*/
void	get_money(t_vars *game);

/*
* objects.c
*/
int		c_rand(int spread, int i, t_list *cleaner);
int		add_random_coins(t_vars *game, t_coin *coins, t_list *cleaner);
int		add_random_doors(t_vars *game, t_door *doors, t_list *cleaner);
void	fill_coins_doors(t_vars *game, t_coin *coins, t_door *doors);
void	objects_count(t_vars *game, int *c, int *d);

/*
* objects_init.c
*/
void	door_init(t_door *doors, int *current, int j, int i);
void	coin_init(t_coin *coins, int *current, int j, int i);
int		objects_init(t_vars *game, t_list *cleaner);
int		player_init(t_player *player, int i, int k, char *side);

#endif