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
			printf("Hello!");
			
			/* to avoid spam */
			while (readButton()) {;}
		}
		else {
			setRed(false);
			setBlue(false);
			setGreen(false);
		}
		
		/* echo what we get */
		if (DEBUG_UART->ISR & USART_ISR_RXNE) 
			printf("%c", DEBUG_UART->RDR);
	}
}
