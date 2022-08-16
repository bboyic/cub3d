/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaryam <fmaryam@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/14 15:58:00 by fmaryam           #+#    #+#             */
/*   Updated: 2022/08/14 18:00:41 by fmaryam          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "index.h"

int	ft_write(int fd, char *message)
{
	return (write(fd, message, ft_strlen(message)));
}

int	ft_white(char *line)
{
	if (ft_strlen(line) == 1 && line[0] == '\n')
		return (0);
	return (1);
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

int	watch_dogs(char **file_data, int k, int i)
{
	int	fl;

	fl = 0;
	if (file_data[k + 1][ft_strlen(file_data[k + 1]) - 1] != '\n')
		fl = 1;
	if ((ft_strlen(file_data[k - 1]) <= i + 2)
		|| (ft_strlen(file_data[k + 1]) <= i + 2 - fl))
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
		return ('N');
	if (i - 1 > 0 && mmap[k]->line[i - 1] == '0')
		return ('W');
	if (i + 1 < mmap[k]->len && mmap[k]->line[i + 1] == '0')
		return ('E');
	if (k + 1 < height && i < mmap[k + 1]->len && mmap[k + 1]->line[i] == '0')
		return ('S');
	return (0);
}
