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

int	ft_skip_white(char *line)
{
	int	i;

	i = 0;
	while (line[i] == ' ')
		i++;
	return (i);
}