#include "index.h"

int	ft_try_open(char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		perror(file);
	return (fd);
}

		// if ((line[i] >= 'a' && line[i] <= 'z')
		// 	|| (line[i] >= 'A' && line <= 'Z')
		// 	|| (line[i] >= '0' && line[i] <= '9'))

// add get_next_line()
// check spaces line
// check \n lines
int	ft_get_file_height(char *file)
{
	int		fd;
	int		height;
	char	*line;

	fd = ft_try_open(file);
	if (fd == -1)
		return (0);
	height = 0;
	line = get_next_line(fd);
	while (line)
	{
		if (ft_white(line))
			height++;
		free(line); // think about free it after loop!
		line = get_next_line(fd);
	}
	close(fd);
	// if height < 9 -> add message
	return (height);
}

int	ft_read_file(char *file, char ***file_data) // > 25 (26)
{
	int		height;
	int		length;
	int		fd;
	char	*line;

	height = ft_get_file_height(file);
	if (height < 9)
		return (1);
	fd = ft_try_open(file);
	if (fd == -1)
		return (1);
	*file_data = malloc(sizeof(char *) * (height + 1));
	(*file_data)[height] = 0;
	if (!(*file_data))
		return (1)
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
	return (0)
}

void	ft_free_mas(void	**mas) // change func direction
{
	int	i;

	i = -1;
	while (mas[++i])
	{
		if (mas[i])
			free(mas[i])
	}
	free(mas);
}

t_map	*ft_map(char *file, t_list *cleaner)
{
	t_map	*map_data;
	char	**file_data;

	if (ft_valid_file(file) || ft_read_file(file, &file_data))
		return (0);
	map_data = malloc(sizeof(t_map) * 1);
	if (!map_data
		|| ft_get_config(map_data, file_data, cleaner)
		|| ft_get_mmap(map_data, file_data, cleaner))
	{
		ft_free_mas(file_data);
		return (0);
	}
	return (map_data);
}

// add all into different massive and then from end to start go check