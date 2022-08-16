/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaryam <fmaryam@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/14 16:00:29 by fmaryam           #+#    #+#             */
/*   Updated: 2022/08/14 17:44:17 by fmaryam          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "index.h"

int	ft_convert_rgb_num(const char *str)
{
	size_t		i;
	int			nb;
	int			fl;

	i = 0;
	nb = 0;
	fl = 0;
	while (str[i] == ' ')
		i++;
	if (ft_strlen(str + i) > 3)
		return (-1);
	while (str[i] >= '0' && str[i] <= '9')
	{
		nb = (nb * 10) + (str[i]) - 48;
		fl = 1;
		i++;
	}
	if (str[i] != '\0' || fl == 0)
		return (-1);
	if (nb > 255)
		return (-1);
	return (nb);
}

int	ft_try_open(char *file, int *fd)
{
	*fd = open(file, O_RDONLY);
	if (*fd == -1)
	{
		perror(file);
		return (1);
	}
	return (0);
}

// check spaces line
// check \n lines
int	ft_get_file_height(char *file, int *height, t_list *cleaner)
{
	int		fd;
	char	*line;

	if (ft_try_open(file, &fd))
		return (1);
	*height = 0;
	line = get_next_line(fd, cleaner);
	while (line)
	{
		if (ft_white(line))
			(*height)++;
		free(line);
		line = get_next_line(fd, cleaner);
	}
	close(fd);
	if (*height < BONUS)
		return (ft_write(2, "Error: Map to small\n"));
	return (0);
}

int	ft_read_file(t_map *map_data, char *file, char ***file_data,
	t_list *cleaner)
{
	int		height;
	int		length;
	int		fd;
	char	*line;

	if (ft_get_file_height(file, &height, cleaner))
		return (1);
	if (ft_try_open(file, &fd))
		return (1);
	*file_data = malloc(sizeof(char *) * (height + 1));
	if (!(*file_data))
		return (ft_write(2, "Error: Allocate file_data\n"));
	(*file_data)[height] = 0;
	map_data->height = height - 6;
	height = -1;
	line = get_next_line(fd, cleaner);
	while (line)
	{
		if (ft_white(line))
			(*file_data)[++height] = line;
		else
			free(line);
		line = get_next_line(fd, cleaner);
	}
	return (0);
}

t_map	*ft_map(char *file, t_player *player, t_list *cleaner)
{
	t_map	*map_data;
	char	**file_data;

	map_data = malloc(sizeof(t_map) * 1);
	if ((!map_data || ft_clslist_add_front(cleaner, map_data))
		&& ft_write(2, "Error: Allocate map_data\n"))
		return (0);
	if (ft_valid_file(file) || ft_read_file(map_data, file,
			&file_data, cleaner))
		return (0);
	if (ft_get_config(map_data, file_data, cleaner)
		|| ft_get_mmap(map_data, file_data + 6, player, cleaner))
	{
		printf("wrong\n");
		ft_free_mas(file_data);
		return (0);
	}
	ft_free_mas(file_data);
	return (map_data);
}
