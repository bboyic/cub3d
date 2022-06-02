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

int ft_white(char *line)
{
	if (ft_strlen(line) == 1 && line[0] == '\n')
		return (1);
	return (0);
}
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
		return (1);
	height = 0;
	line = get_next_line(fd);
	while (line)
	{
		if (!ft_white(line))
			height++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (height);
}

int	ft_read_map(char *file, char ***file_data)
{
	int	height; // is it right?
	int	length;
	int	fd;

	height = ft_get_file_height(file);
}

int	ft_map(char *file)
{
	char	**file_data;

	if (ft_valid_file(file) || ft_read_map(file, &file_data))
		return (0);

}

// add all into different massive and then from end to start go check