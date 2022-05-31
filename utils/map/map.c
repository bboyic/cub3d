#include "index.h"

int	ft_try_open(char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		perror(file);
	return (fd);
}

int	ft_map(char *file)
{

	if (ft_valid(file))
		return (0);
	
}