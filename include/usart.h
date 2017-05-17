#ifndef _UART__H__
#define _UART__H__

#include <stdio.h>
#include "stm32f767xx.h"
#include "config.h"
#include "gpio.h"

typedef enum {
	APB1 =		0,
	SYSCLK =	1,
	HSI_SRC =	2,
	LSE_SRC =	3
} USART_CLK_SRC;
			
int usart_config(USART_TypeDef* usart, USART_CLK_SRC src, uint32_t control[3], uint32_t baud);

/*
#define IS_USART	usart != USART1 && usart != USART2 && usart != USART3 &&	\
					usart != UART4 && usart != UART5 && usart != USART6 &&		\
					usart != UART7 && usart != UART8
*/

#endif
