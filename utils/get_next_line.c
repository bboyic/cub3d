/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaryam <fmaryam@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 19:54:17 by fmaryam           #+#    #+#             */
/*   Updated: 2022/08/14 16:05:41 by fmaryam          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "index.h"

char	*get_next_line(int fd, t_list *cleaner)
{
	static char	*ptr;

	if (read(fd, 0, 0) == -1)
		return (0);
	if (ptr == 0)
	{
		ptr = malloc(sizeof(char) * 1);
		if (!ptr)
			ft_exit(1, cleaner);
		ptr[0] = 0;
	}
	if (put(fd, &ptr, cleaner) && line_size(ptr, '\0') == 0)
	{
		free(ptr);
		ptr = 0;
		return (0);
	}
	return (get_line(&ptr, cleaner));
}
