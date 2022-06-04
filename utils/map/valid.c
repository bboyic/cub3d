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

int	ft_check_name(t_map *map_data, char *line)
{
	if (!ft_strncmp(line, "NO", 2))
		map_data->texture_of_north = ft_get_texture(line + 2);
	else if (!ft_strncmp(line, "SO",2))
		map_data->texture_of_south = ft_get_texture(line + 2);
	else if (!ft_strncmp(line, "WE", 2))
		map_data->texture_of_west = ft_get_texture(line + 2);
	else if (!ft_strncmp(line, "EA", 2))
		map_data->texture_of_east = ft_get_texture(line + 2);
	else if (!ft_strncmp(line, "F", 1))
		map_data->rgb_floor = ft_get_rgb(line + 1);
	else if (!ft_strncmp(line, "C", 1))
		map_data->rgb_ceiling = ft_get_rgb(line + 1);
	else
		return (1);
	return (0);
}