#include "index.h"

int	ft_valid_file(char *file)
{
	int	len;
	int	shift;
	int	fd;

	shift = ft_pos_strchr(file, '/');
	len = ft_strlen(file);
	if (len - shift < 5 || ft_strcmp(file + len - 4, ".cub"))
		return (ft_write(2, "Error: Bad filename\n"));
	return (0);
}

int	ft_check_name(t_map *map_data, char *line, t_list *cleaner)
{
	int	fl;

	fl = 1;
	line += ft_skip_white(line);
	if (!ft_strncmp(line, "NO ", 3)
		&& ft_get_texture(&map_data->texture_of_north, line + 2, cleaner, &fl))
		return (ft_write(2, "Error: North texture is incorrect\n"));
	if (!ft_strncmp(line, "SO ", 3)
		&& ft_get_texture(&map_data->texture_of_south, line + 2, cleaner, &fl))
		return (ft_write(2, "Error: South texture is incorrect\n"));
	if (!ft_strncmp(line, "WE ", 3)
		&& ft_get_texture(&map_data->texture_of_west, line + 2, cleaner, &fl))
		return (ft_write(2, "Error: West texture is incorrect\n"));
	if (!ft_strncmp(line, "EA ", 3)
		&& ft_get_texture(&map_data->texture_of_east, line + 2, cleaner, &fl))
		return (ft_write(2, "Error: East texture is incorrect\n"));
	if (!ft_strncmp(line, "F ", 2)
		&& ft_get_rgb(&map_data->rgb_floor, line + 1, &fl))
		return (ft_write(2, "Error: Floor rgb is incorrect\n"));
	if (!ft_strncmp(line, "C ", 2)
		&& ft_get_rgb(&map_data->rgb_ceiling, line + 1, &fl))
		return (ft_write(2, "Error: Ceiling rgb is incorrect\n"));
	if (fl)
		return (1);
	return (0);
}

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
	if (ft_strlen(str + i) > 3) // only *** nums
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
			&& line[i] != '\n' && line[i] != 'W' // todo: \n is correct to search
			&& line[i] != 'E' && line[i] != '1' && line[i] != ' ')
			return (1);
		if (line[i] != '1' && line[i] != ' ' && line[i] != '\n') // todo: \n is correct to search
		{
			if (i == 0 || !line[i + 1])
				return (1);
			if (watch_dogs(file_data, k, i))
				return (1);
		}
		if ((line[i] == 'N' || line[i] == 'S'
			|| line[i] == 'W' || line[i] == 'E')
			&& player_init(player, i, k, line[i]))
				return (1);
	}
	return (0);
}