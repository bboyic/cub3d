#include "index.h"

int	ft_strlen(const char *s)
{
	int	count;

	count = 0;
	while (*s != '\0')
	{
		count++;
		s++;
	}
	return (count);
}

int	ft_strcmp(char *str1, char *str2)
{
	int	i;

	i = 0;
	while (str1[i] != '\0' && str2[i] != '\0' && str1[i] == str2[i])
		i++;
	if (str1[i] == '\0' && str2[i] == '\0')
		return (0);
	return (1);
}

int	ft_strncmp(char *str1, char *str2, int n)
{
	int	i;

	i = 0;
	while (str1[i] != '\0' && str2[i] != '\0' && str1[i] == str2[i]
		&& i < n)
		i++;
	if (i == n && str1[i - 1] == str2[i - 1])
		return (0);
	return (1);
}

int	ft_pos_strchr(const char *s, int c)
{
	unsigned char	c1;
	int				i;
	int				k;

	i = 0;
	k = -1;
	c1 = (unsigned char)c;
	while (s[i] != '\0')
	{
		if (s[i] == c1)
			k = i;
		i++;
	}
	if (s[i] == c1)
		return (i + 1);
	return (k + 1);
}

void	ft_write(int fd, char *message)
{
	write(fd, message, ft_strlen(message));
}

int	ft_white(char *line)
{
	if (ft_strlen(line) == 1 && line[0] == '\n')
		return (0);
	return (1);
}

int	watch_dogs(char **file_data, int k, int i)
{
	if ((ft_strlen(file_data[k - 1]) < i + 2)
		|| (ft_strlen(file_data[k + 1]) < i + 2))
		return (1);
	if (file_data[k - 1][i] == ' ' || file_data[k - 1][i + 1] == ' '
		|| file_data[k - 1][i - 1] == ' ' || file_data[k][i - 1] == ' '
		|| file_data[k][i + 1] == ' ' || file_data[k + 1][i] == ' '
		|| file_data[k + 1][i + 1] == ' '
		|| file_data[k + 1][i - 1] == ' ')
		return (1);
	return (0);
}

int	watch_dogs_legion(t_dict **mmap, int height, int k, int i)
{
	if (k - 1 > 0 && i < mmap[k - 1]->len && mmap[k - 1]->line[i] == '0')
		return 'N';
	if (i - 1 > 0 && mmap[k]->line[i - 1] == '0')
		return 'W';
	if (i + 1 < mmap[k]->len && mmap[k]->line[i + 1] == '0')
		return 'E';
	if (k + 1 < height && i < mmap[k + 1]->len && mmap[k + 1]->line[i] == '0')
		return 'S';
	return (0);
}