#include "index.h"

int	ft_skip_white(char *line)
{
	int	i;

	i = 0;
	while (line[i] == ' ')
		i++;
	return (i);
}

// int	ft_parse_line(t_map map_data, char *line, t_list *cleaner)
// {
// 	int	res;

// 	res = ft_check_name(map_data, line + ft_skip_white(line), cleaner);
// 	if (res > 0)
// 		return (1);
// }

int	ft_get_texture(char *texture, char *line, t_list *cleaner)
{
	int		i;
	int		fd; //xmm or not?

	line += ft_skip_white(line);
	texture = malloc(sizeof(char *) * ft_strlen(line));
	if (!texture || ft_clslist_add_front(cleaner, texture))
		return (1);
	i = -1;
	while (line[++i])
		texture[i] = line[i];
	fd = open(texture, O_RDONLY);
	if (fd == -1)
	{
		ft_write(2, "Can't open the texture");
		ft_write(2, texture);
		ft_write(2, "\n");
		free(texture);
		return (1);
	}
	close(fd);
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

int	ft_get_rgb(int	*rgb_int[], char *line)
{
	int	size;
	char	**rgb_char;

	rgb_char = ft_split(line + ft_skip_white(line), ',');
	if (!rgb_char || ft_rgb_size(rgb_char))
		return (1);
	size = -1;
	while (rgb_char[++size])
	{
		(*rgb_int)[size] = ft_atoi(rgb_char[size]); // todo add atoi
		if ((*rgb_int)[size] < 0 || (*rgb_int)[size] > 255)
		{
			ft_write(2, "RGB error\n");
			ft_free_mas(rgb_char);
			return (1);
		}
	}
	ft_free_mas(rgb_char);
	return (0);
}

int	ft_get_config(t_map *map_data, char **file_data, t_list *cleaner)
{
	int	i;
	int	count;

	i = -1;
	count = 0;
	while (file_data[++i])
	{
		if (count == 6)
			break ;
		if (ft_check_name(map_data, file_data[i], cleaner)) // check it
			return (1);
		else
			count++;
	}
	return (0);
}