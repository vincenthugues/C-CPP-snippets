#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>

#define TO_UPPER(c) ((c) - 'a' + 'A')

void mexican_wave()
{
	int add = 1; // Go right at first
	
	// Loop until we've gone back
	for (int i = 0; i >= 0; i += add)
	{
		// Print all letters, switching one to uppercase
		for (int j = 0; j != 26; ++j)
			mvaddch(0, j, (j == i) ? TO_UPPER('a' + j) : ('a' + j));
		refresh();
		
		// Pause for 1/8th of a second
		usleep(125000);
		
		// Once we've reached the end, go back to the left
		if (i == 25)
			add = -1;
	}
}

int main()
{
	initscr();
	noecho();
	
	mexican_wave();
	
	getch();
	endwin();
	
	return 0;
}
