#include "../include/nuc144.h"

void nuc144_ioInit(void) {
	gpio_setClock(GPIOB, true);
	gpio_setClock(GPIOC, true);
	gpio_setMode(GPIOB, 0, OUTPUT);
	gpio_setMode(GPIOB, 7, OUTPUT);
	gpio_setMode(GPIOB, 14, OUTPUT);
	gpio_setMode(GPIOC, 13, INPUT);
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

bool readButton(void) {
	return gpio_readPin(GPIOC, BUTTON_PIN);
}
