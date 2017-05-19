#ifndef _CONFIG__H__
#define _CONFIG__H__

#include <stdint.h>

#define DEBUG_UART	USB_UART
#define DEBUG_BAUD	115200

/* Oscillator Values */
#define HSE_VALUE	((uint32_t) 8000000) 
#define HSI_VALUE	((uint32_t) 16000000) 
#define LSE_VALUE	((uint32_t)	32768)

/* Sometimes documentation refers to sys clock as HCLK */
#define HCLK		SystemCoreClock

extern uint32_t SystemCoreClock;
extern volatile unsigned int ticks;

#define APB1_F	SystemCoreClock >> APBPrescTable[(RCC->CFGR >> RCC_CFGR_PPRE1_Pos)]
#define APB2_F	SystemCoreClock >> APBPrescTable[(RCC->CFGR >> RCC_CFGR_PPRE2_Pos)]

/************************* Miscellaneous Configuration ************************/
/* Uncomment the following line if you need to relocate your vector Table in
   Internal SRAM. */
/* #define VECT_TAB_SRAM */
#define VECT_TAB_OFFSET  0x00 /* Vector Table base offset, multiple of 0x200. */
/******************************************************************************/

#endif
