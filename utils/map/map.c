#include "index.h"

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
int	ft_get_file_height(char *file, int *height)
{
	int		fd;
	char	*line;

	if (ft_try_open(file, &fd))
		return (1);
	*height = 0;
	line = get_next_line(fd);
	while (line)
	{
		if (ft_white(line))
			(*height)++;
		free(line); // todo: think about free it after loop!
		line = get_next_line(fd);
	}
	close(fd);
	if (height < 9)
		return (ft_write(2, "Error: Map to small\n"));
	return (0);
}

int	ft_read_file(t_map *map_data, char *file, char ***file_data) // > 25 (26)
{
	int		height;
	int		length;
	int		fd;
	char	*line;

	if (ft_get_file_height(file, &height))
		return (1);
	if (ft_try_open(file, &fd))
		return (1);
	*file_data = malloc(sizeof(char *) * (height + 1));
	if (!(*file_data))
		return (ft_write(2, "Error: Allocate file_data\n"));
	(*file_data)[height] = 0;
	map_data->height = height - 6;
	height = -1;
	line = get_next_line(fd);
	while (line)
	{
		if (ft_white(line))
			(*file_data)[++height] = line;
		else
			free(line);
		line = get_next_line(fd);
	}
	return (0);
}

t_map	*ft_map(char *file, t_player *player, t_list *cleaner)
{
	t_map	*map_data;
	char	**file_data;

	map_data = malloc(sizeof(t_map) * 1);
	if (!map_data || ft_clslist_add_front(cleaner, map_data))
		return (!ft_write(2, "Error: Allocate map_data\n"));
	if (ft_valid_file(file) || ft_read_file(map_data, file, &file_data))
		return (0);
	if (ft_get_config(map_data, file_data, cleaner)
		|| ft_get_mmap(map_data, file_data + 6, player, cleaner))
	{
		ft_free_mas(file_data);
		return (0);
	}
	return (map_data);
}