#include "index.h"

int	ft_skip_white(char *line)
{
	int	i;

	i = 0;
	while (line[i] == ' ')
		i++;
	return (i);
}

int	ft_parse_line(char *line)
{
	if (ft_check_name(line + ft_skip_white(line)))
		return (1);
	
}

char	*ft_get_texture(char *line)
{
	char	*texture;
	int		i;

	line += ft_skip_white(line);
	i = -1;
	while (line[++i])
	{
		
		if (line[++i])
	}
}

int	ft_get_config(t_map *map_data, char **file_data)
{
	int	i;
	int	count;

	i = -1;
	count = 0;
	while (file_data[++i])
	{
		if (count == 6)
			break ;
		if (ft_parse_line(map_data, file_data[i]))
			return (1);
		else
			count++;
	}
	return (0);
}