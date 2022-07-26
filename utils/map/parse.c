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

int	ft_get_texture(char **texture, char *line, t_list *cleaner, int *fl)
{
	int		i;
	int		fd; //xmm or not?

	line += ft_skip_white(line);
	// printf("%s\n", line);
	*texture = malloc(sizeof(char) * (ft_strlen(line) + 1));
	if (!(*texture) || ft_clslist_add_front(cleaner, (*texture)))
		return (1);
	(*texture)[ft_strlen(line)] = 0;
	i = -1;
	while (line[++i])
		(*texture)[i] = line[i];
	// fd = open((*texture), O_RDONLY);
	// if (fd == -1)
	// {
	// 	ft_write(2, "Can't open the texture");
	// 	ft_write(2, (*texture));
	// 	ft_write(2, "\n");
	// 	free((*texture));
	// 	return (1);
	// }
	// close(fd);
	*fl = 0;
	return (0);
}

int	ft_get_rgb(int	(*rgb_int)[], char *line, int *fl)
{
	int	size;
	char	**rgb_char;

	rgb_char = ft_split(line + ft_skip_white(line), ',');
	if (!rgb_char || ft_rgb_size(rgb_char))
		return (1);
	rgb_char[2][ft_strlen(rgb_char[2]) - 1] = '\0';
	size = -1;
	while (rgb_char[++size])
	{
		(*rgb_int)[size] = ft_convert_rgb_num(rgb_char[size]); // if white spaces after last num it is not correct right now
		if ((*rgb_int)[size] < 0)
		{
			ft_write(2, "RGB error\n");
			ft_free_mas(rgb_char);
			return (1);
		}
	}
	ft_free_mas(rgb_char);
	*fl = 0;
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


// think about
// every (0) must not have any ' ' around

int	ft_copy_into_mmap(t_map *map_data, char **file_data, t_list *cleaner, int i)
{
	int	j;

	j = -1;
	// printf("i am in ft_copy_into_mmap\n");
	map_data->mmap[i] = malloc(sizeof(t_dict) * 1);
	if (!map_data->mmap[i]
		|| ft_clslist_add_front(cleaner, map_data->mmap[i]))
		return (1);
	map_data->mmap[i]->len = ft_strlen(file_data[i]) - 1;
	map_data->mmap[i]->line
		= malloc(sizeof(char) * (map_data->mmap[i]->len + 1));
	if (!map_data->mmap[i]->line
		|| ft_clslist_add_front(cleaner, map_data->mmap[i]->line))
		return (1);
	map_data->mmap[i]->line[map_data->mmap[i]->len] = 0;
	while (file_data[i][++j])
		map_data->mmap[i]->line[j] = file_data[i][j];
	return (0);
}

// add error mgs
int	ft_get_mmap(t_map *map_data, char **file_data, t_player *player, t_list *cleaner)
{
	int	i;
	int	ct;

	i = -1;
	ct = 0;
	map_data->mmap = malloc(sizeof(t_dict *) * (map_data->height + 1));
	if (!map_data->mmap || ft_clslist_add_front(cleaner, map_data->mmap))
		return (1);
	map_data->mmap[map_data->height] = 0;
	while (file_data[++i])
	{
		if ((i == 0 || !file_data[i + 1])
			&& ft_border_line(file_data[i]))
			return (1);
		if ((i > 0 && file_data[i + 1])
			&& ft_inside_line(file_data, file_data[i], i, player))
			return (1);
		if (ct > 1)
			return (1);
		if (ft_copy_into_mmap(map_data, file_data, cleaner, i))
			return (1);
	}
	if (file_data[i - 1][map_data->mmap[map_data->height - 1]->len] != '\n')
		map_data->mmap[map_data->height - 1]->len++;
	return (0);
}