#ifndef MAIN_H
# define	MAIN_H

#include <mlx.h>
#include <unistd.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cub3d.h>
#define PI 3.14159265359
#define RD 0.0174533

/*
* cleaner.c
*/
int		ft_clslist_add_front(t_list *cleaner, void *param);
t_list	*ft_new_clsnode(void *param);
void	ft_cleaner(t_list *cleaner);

/*
* valid.c
*/

/*
* string.c
*/
int		ft_strcmp(char *str1, char *str2);
int		ft_strlen(const char *s);
void	*ft_write(int fd, char *message);
int		ft_pos_strchr(const char *s, int c);



#endif