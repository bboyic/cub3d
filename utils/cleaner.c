/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaner.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaryam <fmaryam@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/14 15:56:57 by fmaryam           #+#    #+#             */
/*   Updated: 2022/08/14 18:01:00 by fmaryam          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "index.h"

int	ft_exit(int ex, t_list *cleaner)
{
	ft_cleaner(cleaner);
	printf("Exit with code: %d\n", ex);
	exit(ex);
}

int	ft_clslist_add_front(t_list *cleaner, void *param)
{
	t_list	*new_node;

	new_node = ft_new_clsnode(param);
	if (!new_node)
		return (1);
	new_node->next = cleaner->next;
	cleaner->next = new_node;
	return (0);
}

t_list	*ft_new_clsnode(void *param)
{
	t_list	*new_node;

	new_node = malloc(sizeof(t_list) * 1);
	if (!new_node)
	{
		free(param);
		return (0);
	}
	new_node->next = 0;
	new_node->key = param;
	return (new_node);
}

void	ft_cleaner(t_list *cleaner)
{
	t_list	*next_node;
	t_list	*temp;

	temp = cleaner;
	cleaner = cleaner->next;
	free(temp);
	while (cleaner)
	{
		next_node = cleaner->next;
		if (cleaner->key)
			free(cleaner->key);
		free(cleaner);
		cleaner = next_node;
	}
}

void	ft_free_mas(char **mas)
{
	int	i;

	i = -1;
	while (mas[++i])
	{
		if (mas[i])
			free(mas[i]);
	}
	free(mas);
}
