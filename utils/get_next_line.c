/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaryam <fmaryam@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 19:54:17 by fmaryam           #+#    #+#             */
/*   Updated: 2022/02/08 20:08:30 by fmaryam          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char	*ptr;

	if (read(fd, 0, 0) == -1)
		return (0);
	if (ptr == 0)
	{
		ptr = malloc(sizeof(char) * 1);
		if (!ptr)
			exit(1);
		ptr[0] = 0;
	}
	if (put(fd, &ptr) && line_size(ptr, '\0') == 0)
	{
		free(ptr);
		ptr = 0;
		return (0);
	}
	return (get_line(&ptr));
}
