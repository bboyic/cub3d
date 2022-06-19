/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaryam <fmaryam@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 19:54:20 by fmaryam           #+#    #+#             */
/*   Updated: 2022/06/19 16:38:10 by fmaryam          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 16
# endif

// # include <unistd.h>
// # include <stdlib.h>
// # include <fcntl.h>

char	*get_next_line(int fd);
int		line_size(char *ptr, char h);
int		add(char **ptr, char buf[], int size);
int		put(int fd, char **ptr);
char	*get_line(char **ptr);

#endif
