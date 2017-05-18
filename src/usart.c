#include "../include/usart.h"

/* needed to retarget printf */
FILE __stdout;
struct __FILE {
    int dummy;
};

int fputc(int ch, FILE *f) {
	while (!(DEBUG_UART->ISR & USART_ISR_TXE)) {;}
	DEBUG_UART->TDR = ch;
	return 0;
}

int fgetc(FILE *f) {
	while (!(DEBUG_UART->ISR & USART_ISR_RXNE)) {;}
	return DEBUG_UART->RDR;
}

/*
static int verify_usart(USART_TypeDef* usart) {
	if (IS_USART) return -1;
	return 0;
}
*/

static int usart_enableClock(USART_TypeDef* usart) {
	
	__IO uint32_t *reg;
	uint8_t bit;
	
	switch ((uint32_t) usart) {
		case USART1_BASE: 
			reg = &RCC->APB2ENR;
			bit = 4;
			break;
		case USART2_BASE:
			reg = &RCC->APB1ENR;
			bit = 17;
			break;
		case USART3_BASE:
			reg = &RCC->APB1ENR;
			bit = 18;
			break;
		case UART4_BASE:
			reg = &RCC->APB1ENR;
			bit = 19;
			break;
		case UART5_BASE:
			reg = &RCC->APB1ENR;
			bit = 20;
			break;
		case USART6_BASE:
			reg = &RCC->APB2ENR;
			bit = 5;
			break;
		case UART7_BASE:
			reg = &RCC->APB1ENR;
			bit = 30;
			break;
		case UART8_BASE:
			reg = &RCC->APB1ENR;
			bit = 31;
			break;
		default: return -1;
	}
	
	*reg |= 0x1 << bit;
	
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
	
	uint32_t usartDiv, fck, remainder;
	
	/* turn this USART off if it's on */
	if (usart->CR1 & 0x1) {
		usart->CR1 &= ~0x1;
		while (usart->CR1 & 0x1) {;}
	}
	
	if (usart_setClockSource(usart, src)) return -1;
	
	usart_enableClock(usart); /* don't need to check */
	
	if (control) {
		usart->CR1 = control[0] & ~(0xD);	/* don't set TE, RE, UE yet */
		usart->CR2 = control[1];
		usart->CR3 = control[2];
	}
	
	/* setup baud, fck / USARTDIV */
	switch (src) {
		case APB1:		fck = APB1_F; break;
		case SYSCLK:	fck = SystemCoreClock; break;
		case HSI_SRC:	fck = HSI_VALUE; break;
		case LSE_SRC:	return -1; /* not enabled */
	}
	
	remainder = fck % baud;
	usartDiv = fck / baud;
	
	if (remainder > baud / 2) usartDiv++;
	
	/* not sure how to handle OVER8 being set */
	usart->BRR = usartDiv;
	
	usart->CR1 = 0xD; 		/* set TE, RE, UE */
	usart->ICR |= 0x21Bf5;	/* clear any pending interrupts */
	
	return 0;
}
