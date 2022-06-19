/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaryam <fmaryam@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 19:54:32 by fmaryam           #+#    #+#             */
/*   Updated: 2022/02/09 11:12:21 by fmaryam          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	line_size(char *ptr, char h)
{
	int	i;

	i = 0;
	while (ptr[i] != '\0' && ptr[i] != h)
		i++;
	return (i);
}

int	add(char **ptr, char buf[], int size)
{
	int		size_ptr;
	char	*temp;
	int		i;
	int		fl;

	i = 0;
	fl = 0;
	size_ptr = line_size(*ptr, '\0');
	temp = (char *) malloc(sizeof(char) * (size + size_ptr + 1));
	while (i < size_ptr)
	{
		temp[i] = (*ptr)[i];
		i++;
	}
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

int	put(int fd, char **ptr)
{
	char	buf[BUFFER_SIZE];
	int		ret;

	while (1)
	{
		ret = read(fd, buf, BUFFER_SIZE);
		if (ret == 0)
			return (1);
		if (add(ptr, buf, ret))
			return (0);
	}
}

void	allocate(char **ptr, int strlen_n, char **line, char **new_ptr)
{
	*line = malloc(sizeof(char) * (strlen_n + 2));
	*new_ptr = malloc(sizeof (char) * (line_size(*ptr, '\0') - strlen_n + 1));
	if (!*line || !*new_ptr)
		exit(1);
	(*new_ptr[0]) = '\0';
}

char	*get_line(char **ptr)
{
	int		strlen_n;
	char	*line;
	char	*new_ptr;
	int		i;

	i = 0;
	strlen_n = line_size(*ptr, '\n');
	allocate(ptr, strlen_n, &line, &new_ptr);
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
