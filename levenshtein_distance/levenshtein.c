#include <string.h>

#include "levenshtein.h"

int	min(int a, int b, int c)
{
	return (a < b)
		? (a < c ? a : c)
		: (b < c ? b : c);
}

int	indicator_function(int a, int b)
{
	return a == b ? 0 : 1;
}

int	levenshtein(char *str1, char *str2)
{
	int i, j;
	int len1 = strlen(str1);
	int len2 = strlen(str2);
	int tab[(len2 + 1) * (len1 + 1)];
	
	tab[0] = 0;
	
	for (i = 1; i <= len2; ++i)
		tab[i * len2] = tab[(i - 1) * len2] + 1;
	
	for (j = 1; j <= len1; ++j)
		tab[j] = tab[j - 1] + 1;
	
	for (i = 1; i <= len2; ++i)
		for (j = 1; j <= len1; ++j)
			tab[i * len2 + j] = min(
				tab[(i - 1) * len2 + j] + 1,
				tab[i * len2 + j - 1] + 1,
				tab[(i - 1) * len2 + j - 1] + indicator_function(str1[j - 1], str2[i - 1]));
	
	return tab[len2 * len2 + len1];
}
