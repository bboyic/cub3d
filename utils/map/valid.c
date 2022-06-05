#include "index.h"

int	ft_valid_file(char *file)
{
	int	len;
	int	shift;
	int	fd;

	shift = ft_pos_strchr(file, '/');
	len = ft_strlen(file);
	if (len - shift < 5 || ft_strcmp(file + len - 4, ".cub"))
	{
		ft_write(2, "Error: Bad filename\n");
		return (1);
	}
	return (0);
}

// is not right construct (if -> else)
int	ft_check_name(t_map *map_data, char *line, t_list *cleaner)
{
	int	fl;

	fl = 1;
	line += ft_skip_white(file_data[i]);
	if (!ft_strncmp(line, "NO", 2)
		&& ft_get_texture(map_data->texture_of_north, line + 2, cleaner))
		return (-1);
	if (!ft_strncmp(line, "SO",2)
		&& ft_get_texture(map_data->texture_of_south, line + 2, cleaner))
		return (-1);
	if (!ft_strncmp(line, "WE", 2)
		&& ft_get_texture(map_data->texture_of_west, line + 2, cleaner))
		return (-1);
	if (!ft_strncmp(line, "EA", 2)
		&& ft_get_texture(map_data->texture_of_east, line + 2, cleaner))
		return (-1);
	if (!ft_strncmp(line, "F", 1)
		&& ft_get_rgb(&map_data->rgb_floor, line + 1))
		return (-1);
	if (!ft_strncmp(line, "C", 1)
		&& ft_get_rgb(&map_data->rgb_ceiling, line + 1))
		return (-1);
	if (fl)
		return (1);
	return (0);
}

int	ft_rgb_size(char **rgb_char)
{
	int	size;

	size = 0;
	while (rgb_char[size])
		size++;
	if (size != 3)
	{
		ft_free_mas(rgb_char);
		return (1);
	}
	return (0);
}

int	ft_convert_rgb_num(const char *str)
{
	size_t		i;
	int			nb;
	int			count;
	char		s[19];

	i = 0;
	nb = 0;
	while (str[i] == ' ')
		i++;
	if (ft_strlen(str + i) > 3) // only *** nums
		return (-1);
	while (str[i] >= '0' && str[i] <= '9')
	{
		nb = (nb * 10) + (str[i]) - 48;
		i++;
	}
	if (str[i] != '\0')
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
		if (line[i] != ' ' || line[i] != '1')
			return (1);
	}
	return (0);
}

int	ft_inside_line(char *file_data, char *line, int k, int *ct)
{
	int	i;

	i = -1;
	while (line[++i])
	{
		if (line[i] == 'N' || line[i] == 'S'
			|| line[i] == 'W' || line[i] == 'E')
			*ct++;
		if (line[i] == '0' || line[i] == 'N' || line[i] == 'S'
			|| line[i] == 'W' || line[i] == 'E')
		{
			if (i == 0 || !line[i + 1])
				return (1);
			if ((ft_strlen(file_data[k - 1]) < i + 2)
				|| (ft_strlen(file_data[k + 1]) < i + 2))
				return (1);
			if (file_data[k - 1][i] == ' ' || file_data[k - 1][i + 1] == ' '
				|| file_data[k - 1][i - 1] == ' ' || file_data[k][i - 1] == ' '
				|| file_data[k][i + 1] == ' ' || file_data[k + 1][i] == ' '
				|| file_data[k + 1][i + 1] == ' '
				|| file_data[k + 1][i - 1] == ' ')
				return (1);
		}
	}
	return (0);
}