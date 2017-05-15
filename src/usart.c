#include "../include/usart.h"

static int verify_usart(USART_TypeDef* usart) {
	if (IS_USART) return -1;
	return 0;
}

static int usart_setClockSource(USART_TypeDef* usart, USART_CLK_SRC src) {
	
	uint8_t pin_num = 0;
	
	if (src > 3) return -1;
	
	switch ((uint32_t) usart) {
		case USART1_BASE: pin_num =  0; break;
		case USART2_BASE: pin_num =  2; break;
		case USART3_BASE: pin_num =  4; break;
		case UART4_BASE:  pin_num =  6; break;
		case UART5_BASE:  pin_num =  8; break;
		case USART6_BASE: pin_num = 10; break;
		case UART7_BASE:  pin_num = 12; break;
		case UART8_BASE:  pin_num = 14; break;
		default: return -1;
	}
	
	RCC->DCKCFGR2 &= ~(0x3 << pin_num);
	RCC->DCKCFGR2 |= src << pin_num;
	
	return 0;
}

int usart_config(USART_TypeDef* usart, USART_CLK_SRC src, uint32_t control[3], uint32_t baud) {
	
	if (usart_setClockSource(usart, src)) return -1;
	
	usart->CR1 = control[0];
	usart->CR2 = control[1];
	usart->CR3 = control[2];
	
	/* TODO: setup baud */
	
	return 0;
}
