#include <unistd.h>
#include <string.h>
#include <stdio.h>

#define IS_UPPER(c) ((c) >= 'A' && (c) <= 'Z')
#define IS_LOWER(c) ((c) >= 'a' && (c) <= 'z')

#define TO_UPPER(c) ((c) - 'a' + 'A')
#define TO_LOWER(c) ((c) - 'A' + 'a')

void process_string(const char *s1, const char *s2)
{
	for (int i = 0; s1[i]; ++i)
	{
		char c = s1[i];
		
		if (IS_UPPER(c) && IS_LOWER(s2[i]))
			c = TO_LOWER(c);
		else if (IS_LOWER(c) && IS_UPPER(s2[i]))
			c = TO_UPPER(c);
		
		write(1, &c, 1);
	}
	write(1, "\n", 1);
}

void swap_capitalization(const char *s1, const char *s2)
{
	process_string(s1, s2);
	process_string(s2, s1);
}

int main(int argc, char **argv)
{
	if (argc == 3 && strlen(argv[1]) == strlen(argv[2]))
		swap_capitalization(argv[1], argv[2]);
	else
	{
		printf("Usage: ./swap_capitalization s1 s2\n");
		printf("s1 & s2 being character strings of the same length\n");
		printf("Example: ./swap_capitalization \"PRogrammiNG puzZLes & CODe golf\" \"SdlkhkfaladlKsdlalksdg7ldklDgsl\"\n");
	}
	
	return 0;
}
