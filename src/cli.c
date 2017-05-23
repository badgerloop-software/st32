#include "../include/cli.h"

volatile unsigned int availableCount = 0;

inline void printPrompt(void) {
	printf("\n=> ");
}

void processCommand(void) {
	if (availableCount) {
		
		/* need to pull the characters out of the buffer */
		
		printPrompt();
		availableCount--;
	}
}
