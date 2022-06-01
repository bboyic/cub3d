#include "index.h"

int	ft_try_open(char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		perror(file);
	return (fd);
}

int	ft_get_file_height(char *file)
{
	int	fd;
	int	height;

	fd = ft_try_open(file);
	if (fd == -1)
		return (1);
	
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