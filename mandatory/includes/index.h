#ifndef MAIN_H
# define	MAIN_H

// #include <mlx.h>
#include <unistd.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cub3d.h"
#include "get_next_line.h"
#define PI 3.14159265359
#define RD 0.0174533

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
int		ft_strcmp(char *str1, char *str2);
int		ft_strncmp(char *str1, char *str2, int n);
int		ft_strlen(const char *s);
void	*ft_write(int fd, char *message);
int		ft_pos_strchr(const char *s, int c);
int		ft_white(char *line);

/*
* split.c
*/
char	**ft_split(char const *s, char c);

/*
* map.c
*/
t_map	*ft_map(char *file, t_list *cleaner);
int	ft_read_file(t_map *map_data, char *file, char ***file_data);
int	ft_get_file_height(char *file);
int	ft_try_open(char *file);

/*
* parse.c
*/
int	ft_skip_white(char *line);
int	ft_get_texture(char **texture, char *line, t_list *cleaner, int *fl);
int	ft_get_rgb(int	(*rgb_int)[], char *line, int *fl);
int	ft_get_config(t_map *map_data, char **file_data, t_list *cleaner);
int	ft_copy_into_mmap(t_map *map_data, char **file_data, t_list *cleaner, int i);
int	ft_get_mmap(t_map *map_data, char **file_data, t_list *cleaner);
/*
* valid.c
*/
int	ft_valid_file(char *file);
int	ft_check_name(t_map *map_data, char *line, t_list *cleaner);
int	ft_rgb_size(char **rgb_char);
int	ft_convert_rgb_num(const char *str);
int	ft_border_line(char *line);
int	ft_inside_line(char **file_data, char *line, int k, int *ct);


#endif