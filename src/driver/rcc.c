#include "../../include/driver/rcc.h"

/* can be used to roughly keep track of time, implement timeouts and blocking delays */
/* this 32-bit count overflows after 49.7 days */
volatile unsigned int ticks = 0;
void SysTick_Handler(void) { ticks++; }

void rcc_changeClockSrc() {
	
}

void rcc_setPLLs() {
	
}
