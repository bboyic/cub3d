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

int	ft_check_name(char *line)
{
	
}

int	ft_get_config(t_map *map_data, char **file_data)
{
	int	i;

	i = -1;
	while (file_data[++i])
	{
		if (ft_parse_line(map_data, file_data[i]))
			return (1);
	}
	return (0);
}