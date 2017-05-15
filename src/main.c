#include "../include/main.h"

void fault(void) {
	
	setRed(true);
	
	while (1) {
		
	}
}

int main(void) {

	if (initialize()) fault();
	
	while (1) {
		if (readButton()) {
			setRed(true);
			setBlue(true);
			setGreen(true);
		}
		else {
			setRed(false);
			setBlue(false);
			setGreen(false);
		}
	}
}
