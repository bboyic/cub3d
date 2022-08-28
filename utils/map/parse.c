/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaryam <fmaryam@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/14 16:00:24 by fmaryam           #+#    #+#             */
/*   Updated: 2022/08/28 13:05:33 by fmaryam          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "index.h"

int	ft_get_texture(char **texture, char *line, t_list *cleaner, int *fl)
{
	int		i;
	int		fd;

	line += ft_skip_white(line);
	if (*texture)
		return (ft_write(2, "Error: Double allocate\n"));
	*texture = malloc(sizeof(char) * (ft_strlen(line)));
	if (!(*texture) || ft_clslist_add_front(cleaner, (*texture)))
		return (1);
	i = -1;
	while (line[++i])
		(*texture)[i] = line[i];
	(*texture)[ft_strlen(line) - 1] = 0;
	fd = open((*texture), O_RDONLY);
	if (fd == -1)
	{
		ft_write(2, "Error: Can't open the texture ");
		ft_write(2, (*texture));
		ft_write(2, "\n");
		return (1);
	}
	close(fd);
	*fl = 0;
	return (0);
}

int	ft_get_rgb(int (*rgb_int)[], char *line, int *fl)
{
	int		size;
	char	**rgb_char;

	rgb_char = ft_split(line + ft_skip_white(line), ',');
	if (!rgb_char || ft_rgb_size(rgb_char))
		return (1);
	rgb_char[2][ft_strlen(rgb_char[2]) - 1] = '\0';
	size = -1;
	while (rgb_char[++size])
	{
		(*rgb_int)[size] = ft_convert_rgb_num(rgb_char[size]);
		if ((*rgb_int)[size] < 0)
		{
			ft_free_mas(rgb_char);
			return (1);
		}
	}
	ft_free_mas(rgb_char);
	*fl = 0;
	return (0);
}

int	ft_get_config(t_map *map_data, char **file_data, t_list *cleaner)
{
	int	i;
	int	count;

	i = -1;
	count = 0;
	while (file_data[++i])
	{
		if (count == 6)
			break ;
		if (ft_check_name(map_data, file_data[i], cleaner))
			return (1);
		count++;
	}
	return (0);
}

int	ft_copy_into_mmap(t_map *map_data, char **file_data, t_list *cleaner, int i)
{
	int	j;

	j = -1;
	map_data->mmap[i] = malloc(sizeof(t_dict) * 1);
	if (!map_data->mmap[i]
		|| ft_clslist_add_front(cleaner, map_data->mmap[i]))
		return (ft_write(2, "Error: Allocate mmap[i]\n"));
	map_data->mmap[i]->len = ft_strlen(file_data[i]) - 1;
	if (file_data[i][ft_strlen(file_data[i]) - 1] != '\n')
		map_data->mmap[i]->len++;
	map_data->mmap[i]->line
		= malloc(sizeof(char) * (map_data->mmap[i]->len + 1));
	if (!map_data->mmap[i]->line
		|| ft_clslist_add_front(cleaner, map_data->mmap[i]->line))
		return (ft_write(2, "Error: Allocate line\n"));
	while (file_data[i][++j])
		map_data->mmap[i]->line[j] = file_data[i][j];
	map_data->mmap[i]->line[map_data->mmap[i]->len] = 0;
	return (0);
}

int	ft_get_mmap(t_map *map_data, char **file_data, t_player *player,
	t_list *cleaner)
{
	int	i;

	i = -1;
	map_data->mmap = malloc(sizeof(t_dict *) * (map_data->height + 1));
	if (!map_data->mmap || ft_clslist_add_front(cleaner, map_data->mmap))
		return (ft_write(2, "Error: Allocate mmap\n"));
	map_data->mmap[map_data->height] = 0;
	while (file_data[++i])
	{
		if ((i == 0 || !file_data[i + 1])
			&& ft_border_line(file_data[i]))
			return (ft_write(2, "Error: Map get in trouble\n"));
		if ((i > 0 && file_data[i + 1])
			&& ft_inside_line(file_data, file_data[i], i, player))
			return (ft_write(2, "Error: Map get in trouble\n"));
		if (ft_copy_into_mmap(map_data, file_data, cleaner, i))
			return (1);
	}
	if (player->x == -1)
		return (ft_write(2, "Error: Where is my hero?\n"));
	return (0);
}
