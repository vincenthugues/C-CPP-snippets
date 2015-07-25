#include <stdio.h>

#include "levenshtein.h"

int main(int argc, char **argv)
{
	if (argc == 3)
		printf("Levenshtein distance: %d\n", levenshtein(argv[1], argv[2]));
	else
		printf("Usage: ./levenshtein \"string1\" \"string2\"\n");
	
	return 0;
}
