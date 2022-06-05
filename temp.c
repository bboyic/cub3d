#include <stdio.h>
#include <stdlib.h>

typedef struct temp {
	int	kek;
	char	*lol;
	int	fuck[3];
}	t_temp;

void	change_stat_mas(int (*mas)[])
{
	(*mas)[0] = 2;
}

t_temp	*get_temp()
{
	t_temp *temp;

	temp = malloc(sizeof(t_temp) * 1);
	temp->kek = 5;
	temp->lol = malloc(sizeof(char) * 1);
	temp->lol[0] = 'a';
	temp->fuck[0] = 1;
	printf("(1)%d %s %d\n", temp->kek, temp->lol, temp->fuck[0]);
	change_stat_mas(&temp->fuck);
	printf("(1)%d %s %d\n", temp->kek, temp->lol, temp->fuck[0]);
	return (temp);
}

void	set_temp(t_temp temp)
{
	printf("(exp)%d %s\n", temp.kek, temp.lol);
}

int main()
{
	// int	lol[3];

	// lol[0] = 1;
	// lol[1] = 2;
	// lol[2] = 3;
	// printf("%d %d %d\n", lol[0], lol[1], lol[2]);
	// char *lol = malloc(sizeof(char) * 3);
	// lol[0] = 'a';
	// lol[1] = 'b';
	// lol[2] = 'c';
	// char *kek = lol;
	// // free(kek);
	// printf("%s", lol);
	t_temp *temp = get_temp();
	printf("(2)%d %s %d\n", temp->kek, temp->lol, temp->fuck[0]);
	
	// t_temp temp;

	// temp.kek = 5;
	// temp.lol = malloc(sizeof(char) * 1);
	// temp.lol[0] = 'a';
	// set_temp(temp);
	// printf("(1)%d %s\n", temp.kek, temp.lol);
}
