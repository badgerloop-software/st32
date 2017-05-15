#include "../include/nuc144.h"

void nuc144_ioInit(void) {
	gpio_setClock(GPIOB, true);	/* LEDs */
	gpio_setClock(GPIOC, true);	/* button */
	gpio_setClock(GPIOD, true);	/* UART */
	
	/* LEDs */
	gpio_setMode(GPIOB, 0, OUTPUT);
	gpio_setMode(GPIOB, 7, OUTPUT);
	gpio_setMode(GPIOB, 14, OUTPUT);
	
	/* button (no need for pull-up or pull-down) */
	gpio_setMode(GPIOC, 13, INPUT);	
	
	/* USART3 -> ST-LINKv2 -> USB virtual COM */
	gpio_setMode(GPIOD, 8, ALT);
	gpio_setMode(GPIOD, 9, ALT);
}

void setRed(bool state) {
	state ? gpio_setPin(GPIOB, RED_PIN) :
			gpio_resetPin(GPIOB, RED_PIN);
}

void setBlue(bool state) {
	state ? gpio_setPin(GPIOB, BLUE_PIN) :
			gpio_resetPin(GPIOB, BLUE_PIN);
}

void setGreen(bool state) {
	state ? gpio_setPin(GPIOB, GREEN_PIN) :
			gpio_resetPin(GPIOB, GREEN_PIN);
}

inline bool readButton(void) {
	return gpio_readPin(GPIOC, BUTTON_PIN);
}


/* experimenting with oscillator pins
 *
 * gpio_setClock(GPIOA, true);
 * gpio_setSpeed(GPIOA, 8, VERY_HIGH_SPEED);
 * gpio_setSpeed(GPIOC, 9, VERY_HIGH_SPEED);
 * gpio_setAlternateFunc(GPIOA, 8, 1);
 * gpio_setAlternateFunc(GPIOC, 9, 1);
 * gpio_setMode(GPIOA, 8, ALT);
 * gpio_setMode(GPIOC, 9, ALT);
 */
