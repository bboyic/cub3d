#include <stdio.h>
#include <stdlib.h>

int main()
{
	// int	lol[3];

	// lol[0] = 1;
	// lol[1] = 2;
	// lol[2] = 3;
	// printf("%d %d %d\n", lol[0], lol[1], lol[2]);
	char *lol = malloc(sizeof(char) * 3);
	lol[0] = 'a';
	lol[1] = 'b';
	lol[2] = 'c';
	char *kek = lol;
	// free(kek);
	printf("%s", lol);
}