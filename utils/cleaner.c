#include "index.h"

int	ft_clslist_add_front(t_list *cleaner, void *param)
{
	t_list	*new_node;

	new_node = ft_new_clsnode(param);
	if (!new_node)
		return (1);
	cleaner->next = new_node;
	return (0);
}

t_list	*ft_new_clsnode(void *param)
{
	t_list	*new_node;

	new_node = malloc(sizeof(t_list) * 1);
	if (!new_node)
		return (0);
	new_node->next = 0;
	new_node->key = param;
	return (new_node);
}

void	ft_cleaner(t_list *cleaner)
{
	t_list	*next_node;

	while (cleaner)
	{
		next_node = cleaner->next;
		if (cleaner->key)
			free(cleaner->key);
		free(cleaner);
		cleaner = next_node;
	}
}

void	ft_free_mas(void	**mas)
{
	int	i;

	i = -1;
	while (mas[++i])
	{
		if (mas[i])
			free(mas[i])
	}
	free(mas);
}