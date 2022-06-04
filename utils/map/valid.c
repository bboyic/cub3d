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

int	ft_check_name(t_map *map_data, char *line, t_list *cleaner)
{
	line += ft_skip_white(file_data[i]);
	if (!ft_strncmp(line, "NO", 2)
		&& ft_get_texture(map_data->texture_of_north, line + 2, cleaner))
		return (-1);
	else if (!ft_strncmp(line, "SO",2)
		&& ft_get_texture(map_data->texture_of_south, line + 2, cleaner))
		return (-1);
	else if (!ft_strncmp(line, "WE", 2)
		&& ft_get_texture(map_data->texture_of_west, line + 2, cleaner))
		return (-1);
	else if (!ft_strncmp(line, "EA", 2)
		&& ft_get_texture(map_data->texture_of_east, line + 2, cleaner))
		return (-1);
	else if (!ft_strncmp(line, "F", 1)
		&& ft_get_rgb(map_data->rgb_floor, line + 1))
		return (-1);
	else if (!ft_strncmp(line, "C", 1)
		&& ft_get_rgb(map_data->rgb_ceiling, line + 1))
		return (-1);
	else
		return (1);
	return (0);
}