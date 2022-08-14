/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaryam <fmaryam@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 19:54:32 by fmaryam           #+#    #+#             */
/*   Updated: 2022/08/14 15:01:04 by fmaryam          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "index.h"

int	line_size(char *ptr, char h)
{
	int	i;

	i = 0;
	while (ptr[i] != '\0' && ptr[i] != h)
		i++;
	return (i);
}

int	add(char **ptr, char buf[], int size, t_list *cleaner)
{
	int		size_ptr;
	char	*temp;
	int		i;
	int		fl;

	i = -1;
	fl = 0;
	size_ptr = line_size(*ptr, '\0');
	temp = (char *) malloc(sizeof(char) * (size + size_ptr + 1));
	if (!temp)
		ft_exit(1, cleaner);
	while (++i < size_ptr)
		temp[i] = (*ptr)[i];
	while (i < size + size_ptr)
	{
		temp[i] = buf[i - size_ptr];
		if (temp[i] == '\n')
			fl = 1;
		i++;
	}
	temp[i] = '\0';
	free(*ptr);
	*ptr = temp;
	return (fl);
}

int	put(int fd, char **ptr, t_list *cleaner)
{
	char	buf[BUFFER_SIZE];
	int		ret;

	while (1)
	{
		ret = read(fd, buf, BUFFER_SIZE);
		if (ret == 0)
			return (1);
		if (add(ptr, buf, ret, cleaner))
			return (0);
	}
}

int	allocate(char **ptr, int strlen_n, char **line, char **new_ptr)
{
	*line = malloc(sizeof(char) * (strlen_n + 2));
	if (!*line)
		return (1);
	*new_ptr = malloc(sizeof (char) * (line_size(*ptr, '\0') - strlen_n + 1));
	if (!*new_ptr)
	{
		free(line);
		return (1);
	}
	(*new_ptr[0]) = '\0';
	return (0);
}

char	*get_line(char **ptr, t_list *cleaner)
{
	int		strlen_n;
	char	*line;
	char	*new_ptr;
	int		i;

	i = 0;
	strlen_n = line_size(*ptr, '\n');
	if (allocate(ptr, strlen_n, &line, &new_ptr))
		ft_exit(1, cleaner);
	while ((*ptr)[i] != '\n' && (*ptr)[i] != '\0')
	{
		line[i] = (*ptr)[i];
		i++;
	}
	line[i] = (*ptr)[i];
	if ((*ptr)[i] != '\0')
		line[++i] = '\0';
	while ((*ptr)[i++] != '\0')
		new_ptr[i - strlen_n - 1 - 1] = (*ptr)[i - 1];
	if (--i - strlen_n >= 1)
		new_ptr[i - strlen_n - 1] = '\0';
	free(*ptr);
	*ptr = new_ptr;
	return (line);
}
