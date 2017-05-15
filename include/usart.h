#ifndef _UART__H__

#include "stm32f767xx.h"

typedef enum {
	APB1 =		0,
	SYSCLK =	1,
	HSI_SRC =	2,
	LSE_SRC =	3
} USART_CLK_SRC;

#define IS_USART	usart != USART1 && usart != USART2 && usart != USART3 &&	\
					usart != UART4 && usart != UART5 && usart != USART6 &&		\
					usart != UART7 && usart != UART8
				


#endif
