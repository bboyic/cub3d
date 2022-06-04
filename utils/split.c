/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaryam <fmaryam@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 16:50:38 by ptopping          #+#    #+#             */
/*   Updated: 2022/06/05 00:15:07 by fmaryam          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "index.h"

static int	count_words(const char *s, char c)
{
	int	count;
	int	flag;

	flag = 1;
	count = 0;
	while (*s != '\0')
	{
		if (*s != c)
		{
			if (flag)
				count++;
			flag = 0;
		}
		else
			flag = 1;
		s++;
	}
	return (count);
}

static int	last_allocate(const char *s, int length, char **strs, int count)
{
	if (*(s + 1) == '\0' && length)
	{
		strs[count] = malloc(sizeof(char) * (length + 1));
		if (!strs[count])
			return (0);
	}
	return (1);
}

static int	allocate(char **strs, const char *s, char c)
{
	int	length;
	int	count;

	length = 0;
	count = 0;
	while (*s != '\0')
	{
		if (*s != c)
			length++;
		else
		{
			if (length)
			{
				strs[count] = malloc(sizeof(char) * (length + 1));
				if (!strs[count])
					return (0);
				count++;
			}
			length = 0;
		}
		if (!last_allocate(s, length, strs, count))
			return (0);
		s++;
	}
	return (1);
}

static void	fill(char **strs, const char *s, char c)
{
	int	length;
	int	count;

	length = 0;
	count = 0;
	while (*s != '\0')
	{
		if (*s != c)
		{
			strs[count][length] = *s;
			length++;
		}
		else
		{
			if (length)
			{
				strs[count][length] = '\0';
				count++;
			}
			length = 0;
		}
		s++;
	}
	if (length)
		strs[count][length] = '\0';
}

//from libft and i guess it isn't perfect ft_split(
//it is wonderful split❤️
char	**ft_split(char const *s, char c)
{
	int		count;
	char	**strs;
	int		i;

	i = -1;
	if (!s)
		return (0);
	count = count_words(s, c);
	strs = malloc(sizeof(char *) * (count + 1));
	if (!strs)
		return (0);
	strs[count] = 0;
	if (!allocate(strs, s, c))
	{
		while (strs[++i])
			free(strs[i]);
		return (0);
	}
	fill(strs, s, c);
	return (strs);
}
