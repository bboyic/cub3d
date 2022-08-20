/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   index.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaryam <fmaryam@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/20 22:26:49 by fmaryam           #+#    #+#             */
/*   Updated: 2022/08/21 00:48:01 by fmaryam          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INDEX_H
# define INDEX_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 16
# endif

# include <unistd.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include "cub3d.h"
# include "mlx.h"

# define PI 3.14159265359
# define RAD 0.0174533
# define START_MAP_X 0
# define START_MAP_Y 0
# define BLOCK_SIZE 512
# define MINI_BLOCK_SIZE 30
# define MINI_H 6
# define MINI_W 6
# define WIN_H 1000
# define WIN_W 1000
# define BONUS 9
# define SPEED 20
# define TEXTURE_SIZE (512.0)
# define WALL_ALIGN (256)
# define MAX_RANGE (100000)
# define RATIO_DISPLAY (300000)

// undefined
# include <fcntl.h>

/*
* cub3d.c
*/
int			main(int ar, char *av[]);
int			render_next_frame(void *data);
int			check_cube(t_vars *mlx, int x, int y);

/*
* init.c
*/
void		wall_init(t_vars *game);
void		game_init(t_vars *game);
void		my_mlx_init(t_vars *game, t_map *map_data);
int			player_init(t_player *player, int i, int k, char *side);

/*
* gnl
*/
char		*get_next_line(int fd, t_list *cleaner);
int			line_size(char *ptr, char h);
int			add(char **ptr, char buf[], int size, t_list *cleaner);
int			put(int fd, char **ptr, t_list *cleaner);
char		*get_line(char **ptr, t_list *cleaner);

/*
* cleaner.c
*/
int			ft_exit(int ex, t_list *cleaner);
int			ft_clslist_add_front(t_list *cleaner, void *param);
t_list		*ft_new_clsnode(void *param);
void		ft_cleaner(t_list *cleaner);
void		ft_free_mas(char **mas);

/*
* string.c
*/
int			ft_write(int fd, char *message);
int			ft_white(char *line, int fl);
int			watch_dogs(char **file_data, int k, int i);
int			watch_dogs_legion(t_dict **mmap, int height, int k, int i);

/*
* string_utils.c
*/
int			ft_skip_white(char *line);
int			ft_strcmp(char *str1, char *str2);
int			ft_strncmp(char *str1, char *str2, int n);
int			ft_strlen(const char *s);
int			ft_pos_strchr(const char *s, int c);

/*
* split.c
*/
char		**ft_split(char const *s, char c);

/*
* map.c
*/
t_map		*ft_map(char *file, t_player *player, t_list *cleaner);
int			ft_read_file(t_map *map_data, char *file, char ***file_data,
				t_list *cleaner);
int			ft_get_file_height(char *file, int *height, t_list *cleaner);
int			ft_try_open(char *file, int *fd);
int			ft_convert_rgb_num(const char *str);

/*
* parse.c
*/
int			ft_get_texture(char **texture, char *line,
				t_list *cleaner, int *fl);
int			ft_get_rgb(int (*rgb_int)[], char *line, int *fl);
int			ft_get_config(t_map *map_data, char **file_data, t_list *cleaner);
int			ft_copy_into_mmap(t_map *map_data, char **file_data,
				t_list *cleaner, int i);
int			ft_get_mmap(t_map *map_data, char **file_data, t_player *player,
				t_list *cleaner);

/*
* valid.c
*/
int			ft_valid_file(char *file);
int			ft_check_name(t_map *map_data, char *line, t_list *cleaner);
int			ft_rgb_size(char **rgb_char);
int			ft_border_line(char *line);
int			ft_inside_line(char **file_data, char *line, int k,
				t_player *player);

/*
* draw.c
*/
void		draw_background(t_vars *mlx);
int			draw_sky(t_vars *mlx, float y, int ray_index);
int			draw_floor(t_vars *mlx, float y, int ray_index);

/*
*ifs_for_move.c
*/
int			front_if(t_vars *mlx);
int			back_if(t_vars *mlx);
int			left_if(t_vars *mlx);
int			right_if(t_vars *mlx);
int			angle_fix(t_vars *mlx);

/*
* move.c
*/
void		sample_move(t_vars *mlx);
void		turn_move(t_vars *mlx);
void		check_move(t_vars *mlx);

/*
* raycast_utils.c
*/
float		find_cubx(t_vars *mlx, t_rayinfo ray);
t_data		find_texture(t_vars *mlx, t_rayinfo ray);
int			find_color(t_vars *mlx, t_rayinfo ray, float y, int new_wall);
int			find_color2(t_vars *mlx, t_rayinfo ray, float y, int new_wall);
float		draw_wall(t_vars *mlx, int new_wall, t_rayinfo ray, int ray_index);

/*
* raycast.c
*/
void		ray_cast(t_rayinfo ray_len, int ray_index, t_vars *mlx);
void		draw_ray(t_vars *mlx);
t_rayinfo	print_line(t_vars *mlx, float degrees, float x, float y);

/*
* pixel.c
*/
void		my_mlx_pixel_put(t_data *data, int x, int y, int color);
int			get_pixel(t_data *img, int x, int y);

/*
* hook.c
*/
int			key_hook(int keycode, t_vars *mlx);
int			key_down(int keycode, t_vars *mlx);
int			mouse_hook(int x, int y, t_vars *mlx);

int			check_cube(t_vars *mlx, int x, int y);

#endif