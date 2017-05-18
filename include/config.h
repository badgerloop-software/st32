#ifndef _CONFIG__H__
#define _CONFIG__H__

#include <stdint.h>

#define DEBUG_UART	USART3

/* Default value of the External oscillator in Hz */
#ifndef	HSE_VALUE
#define HSE_VALUE	((uint32_t) 8000000) 
#endif

/* Value of the Internal oscillator in Hz */
#ifndef	HSI_VALUE
#define HSI_VALUE	((uint32_t) 16000000) 
#endif

extern uint32_t SystemCoreClock;
extern volatile unsigned int ticks;

#define APB1_F	SystemCoreClock >> APBPrescTable[(RCC->CFGR >> 10)]
#define APB2_F	SystemCoreClock >> APBPrescTable[(RCC->CFGR >> 13)]

/************************* Miscellaneous Configuration ************************/
/* Uncomment the following line if you need to relocate your vector Table in
   Internal SRAM. */
/* #define VECT_TAB_SRAM */
#define VECT_TAB_OFFSET  0x00 /* Vector Table base offset, multiple of 0x200. */
/******************************************************************************/

#endif
