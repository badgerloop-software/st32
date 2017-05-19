#ifndef _CONFIG__H__
#define _CONFIG__H__
#include <stdint.h>

/******************************************************************************/
/*                                   Globals                                  */
/******************************************************************************/
#define DEBUG_UART	USB_UART
#define DEBUG_BAUD	115200
extern uint32_t SystemCoreClock;
extern volatile unsigned int ticks;
extern void SystemCoreClockUpdate(void);
/******************************************************************************/
/******************************************************************************/


/******************************************************************************/
/*                                 Oscillator                                 */
/******************************************************************************/
#define HSE_VALUE	((uint32_t) 8000000) 
#define HSI_VALUE	((uint32_t) 16000000) 
#define LSE_VALUE	((uint32_t)	32768)
/** System Clock source            = PLL (HSE w/ HSE_BYP, 8 MHz)
  * SYSCLK(Hz)                     = 160000000 (160 MHz)
  * HCLK(Hz)                       = 160000000 (160 MHz)
  * AHB, APB1, APB2 Prescalars     = 1, 4, 2
  *
  * Constraints:
  * PLLN[8:0] - 50 <= PLLN <= 432 (f_VCO must be between 100-432 MHz)
  * PLLM[5:0] - 2 <= PLLM <= 63 (f_PLL_in must be 1-2 MHz)
  * PLLP[1:0] - do not exceed 180 MHz (0 = 2, 1 = 4, 2 = 6, 3 = 8)
  * PLLQ[3:0] - 2 <= PLLQ <= 15 goal is to create 48 MHz (USB, SDMMC RNG clock src)
  * PLLR[2:0] - 2 <= PLLR <= 7 DSI clock src 
  */
#define PLLN	((uint32_t) 160 << RCC_PLLCFGR_PLLN_Pos)	/* f_VCO = f_PLL_in * (PLLN / PLLM) */
#define PLLM 	(((uint32_t) 4) << RCC_PLLCFGR_PLLM_Pos)	/* 320 MHz = 8 MHz * (160 / 8)		*/
#define PLLP	(((uint32_t) 0) << RCC_PLLCFGR_PLLP_Pos)	/* f_PLL_out = f_VCO / PLLP	(2)		*/
#define PLLQ	(((uint32_t) 10) << RCC_PLLCFGR_PLLQ_Pos)	/* f_USB_SDMMC_RNG = f_VCO / PLLQ	*/
#define PLLR	(((uint32_t) 5) << RCC_PLLCFGR_PLLR_Pos)	/* f_PLL_DSI_out = f_VCO / PLLR		*/
/******************************************************************************/
/******************************************************************************/


/******************************************************************************/
/*                           Utility Definitions                              */
/******************************************************************************/
#define APB1_F	SystemCoreClock >> APBPrescTable[(RCC->CFGR >> RCC_CFGR_PPRE1_Pos)]
#define APB2_F	SystemCoreClock >> APBPrescTable[(RCC->CFGR >> RCC_CFGR_PPRE2_Pos)]
#define HCLK	SystemCoreClock
/******************************************************************************/
/******************************************************************************/


/************************* Miscellaneous Configuration ************************/
/* Uncomment if you need to relocate your vector Table in internal SRAM. */
/* #define VECT_TAB_SRAM */
#define VECT_TAB_OFFSET  0x00 /* Vector Table base offset, multiple of 0x200. */
/******************************************************************************/

#endif
