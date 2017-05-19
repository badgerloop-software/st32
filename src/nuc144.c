#include "../include/nuc144.h"

/* instantiate UART & button + LEDs no matter what */
void nuc144_earlyInit(void) {
	
	/* LEDs */
	gpio_setClock(LED_GPIO, true);
	gpio_setMode(LED_GPIO, GREEN_PIN, OUTPUT);
	gpio_setMode(LED_GPIO, BLUE_PIN, OUTPUT);
	gpio_setMode(LED_GPIO, RED_PIN, OUTPUT);
	
	/* button (no need for pull-up or pull-down) */
	gpio_setClock(BUTTON_GPIO, true);
	gpio_setMode(BUTTON_GPIO, BUTTON_PIN, INPUT);	
	
	/* USART3 -> ST-LINKv2 -> USB virtual COM */
	gpio_setClock(USB_UART_GPIO, true);
	gpio_setSpeed(USB_UART_GPIO, USB_UART_TX, HIGH_SPEED);
	gpio_setSpeed(USB_UART_GPIO, USB_UART_RX, HIGH_SPEED);
	gpio_setMode(USB_UART_GPIO, USB_UART_TX, ALT);
	gpio_setMode(USB_UART_GPIO, USB_UART_RX, ALT);
	gpio_setAlternateFunc(USB_UART_GPIO, USB_UART_TX, 7); /* TODO: define this somewhere? */
	gpio_setAlternateFunc(USB_UART_GPIO, USB_UART_RX, 7); /* TODO: define this somewhere? */
	usart_config(USB_UART, HSI_SRC, NULL, DEBUG_BAUD);
}

int nuc144_ioInit(void) {
	
	/* use this when developing a new driver */
	
	return 0;
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
