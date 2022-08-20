/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaryam <fmaryam@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/14 16:01:45 by fmaryam           #+#    #+#             */
/*   Updated: 2022/08/20 23:38:33 by fmaryam          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "index.h"

int	ft_valid_file(char *file)
{
	int	len;
	int	shift;

	shift = ft_pos_strchr(file, '/');
	len = ft_strlen(file);
	if (len - shift < 5 || ft_strcmp(file + len - 4, ".cub"))
		return (ft_write(2, "Error: Bad filename\n"));
	return (0);
}

int	ft_check_texture_name(t_map *map_data, char *line, t_list *cleaner,
	int *fl)
{
	if (!ft_strncmp(line, "NO ", 3)
		&& ft_get_texture(&map_data->texture_of_north, line + 2, cleaner, fl))
		return (ft_write(2, "Error: North texture is incorrect\n"));
	if (!ft_strncmp(line, "SO ", 3)
		&& ft_get_texture(&map_data->texture_of_south, line + 2, cleaner, fl))
		return (ft_write(2, "Error: South texture is incorrect\n"));
	if (!ft_strncmp(line, "WE ", 3)
		&& ft_get_texture(&map_data->texture_of_west, line + 2, cleaner, fl))
		return (ft_write(2, "Error: West texture is incorrect\n"));
	if (!ft_strncmp(line, "EA ", 3)
		&& ft_get_texture(&map_data->texture_of_east, line + 2, cleaner, fl))
		return (ft_write(2, "Error: East texture is incorrect\n"));
	return (0);
}

int	ft_check_name(t_map *map_data, char *line, t_list *cleaner)
{
	int	fl;

	fl = 1;
	line += ft_skip_white(line);
	if (ft_check_texture_name(map_data, line, cleaner, &fl))
		return (1);
	if (BONUS == 11 && !ft_strncmp(line, "M ", 2)
		&& ft_get_texture(&map_data->sprite_of_coin, line + 1, cleaner, &fl))
		return (ft_write(2, "Error: Money sprite is incorrect\n"));
	if (BONUS == 11 && !ft_strncmp(line, "D ", 2)
		&& ft_get_texture(&map_data->sprite_of_door, line + 1, cleaner, &fl))
		return (ft_write(2, "Error: Door sprite is incorrect\n"));
	if (!ft_strncmp(line, "F ", 2)
		&& ft_get_rgb(&map_data->rgb_floor, line + 1, &fl))
		return (ft_write(2, "Error: Floor rgb is incorrect\n"));
	if (!ft_strncmp(line, "C ", 2)
		&& ft_get_rgb(&map_data->rgb_ceiling, line + 1, &fl))
		return (ft_write(2, "Error: Ceiling rgb is incorrect\n"));
	if (fl)
		return (ft_write(2, "Error: Headers incorrect/incomplete\n"));
	return (0);
}

int	ft_border_line(char *line)
{
	int	i;

	i = -1;
	while (line[++i])
	{
		if (line[i] == '\n' && line[i + 1] == '\0')
			return (0);
		if (line[i] != ' ' && line[i] != '1')
			return (1);
	}
	return (0);
}

int	ft_inside_line(char **file_data, char *line, int k, t_player *player)
{
	int	i;

	i = -1;
	while (line[++i])
	{
		if (line[i] != 'N' && line[i] != 'S' && line[i] != '0'
			&& line[i] != '\n' && line[i] != 'W'
			&& line[i] != 'E' && line[i] != '1' && line[i] != ' ')
			return (1);
		if (line[i] != '1' && line[i] != ' ' && line[i] != '\n')
		{
			if (i == 0 || !line[i + 1])
				return (1);
			if (watch_dogs(file_data, k, i))
				return (1);
		}
		if ((line[i] == 'N' || line[i] == 'S'
				|| line[i] == 'W' || line[i] == 'E')
			&& player_init(player, i, k, &line[i]))
			return (1);
	}
	return (0);
}
