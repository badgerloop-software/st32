#include "../include/main.h"

int main(void) {

	clock_config();
	
	nuc144_earlyInit();

	if (nuc144_ioInit()) fault();
	
	printf("\r\nHCLK: %u kHz\r\n", HCLK / 1000);
	printPrompt();
	
	while (1) {
		
		if (readButton()) {
			setRed(true);
			setBlue(true);
			setGreen(true);
			printf("Seconds: %d\r\n", ticks / 1000);
			printPrompt();
			
			/* to avoid spam */
			while (readButton()) {;}
		}
		
		else {
			setRed(false);
			setBlue(false);
			setGreen(false);
		}
		
		processCommand();
	}
}

void clock_config(void) {

	/* clear PLL_ON, PLLIS2_ON, PLLSAI_ON, HSE_ON */
	RCC->CR &= ~(RCC_CR_PLLSAION | RCC_CR_PLLI2SON | RCC_CR_PLLON | RCC_CR_HSEON);
	
	/* wait for those to be unlocked */
	while (RCC->CR & (RCC_CR_PLLSAIRDY | RCC_CR_PLLI2SRDY | RCC_CR_PLLRDY | RCC_CR_HSERDY)) {;}
	
	/* configure PLLs */
	RCC->PLLCFGR = 0x24003010;	/* set PLL bits to default	*/
		
	/* Set PLL configs */
	RCC->PLLCFGR |= PLLN; RCC->PLLCFGR |= PLLM;
	RCC->PLLCFGR |= PLLP; RCC->PLLCFGR |= PLLQ;
	RCC->PLLCFGR |= PLLR;
		
	/* Clear out default bits, if you clear them first the board gets messed up */
	/* (bonus points if you can answer why that is) */
	RCC->PLLCFGR &= ~PLLN; RCC->PLLCFGR &= ~PLLM;
	RCC->PLLCFGR &= ~PLLP; RCC->PLLCFGR &= ~PLLQ;
	RCC->PLLCFGR &= ~PLLR;
		
	/* set HSE as PLL clock src	*/
	RCC->PLLCFGR |= RCC_PLLCFGR_PLLSRC_HSE;			
		
	/* set microcontroller clock outputs */
	RCC->CFGR =  0x0;						/* make sure it is in reset state							*/
	RCC->CFGR |= 0x0 << RCC_CFGR_MCO2_Pos;	/* MCO2 set to SYSCLK										*/
	RCC->CFGR |= RCC_CFGR_MCO2PRE_Msk;		/* MCO2 prescalar set to 5									*/
	RCC->CFGR |= RCC_CFGR_MCO1;				/* MCO1 set to PLL											*/
	RCC->CFGR |= RCC_CFGR_MCO1PRE_Msk;		/* MCO1 prescalar set to 5									*/
	RCC->CFGR |= RCC_CFGR_RTCPRE_3;			/* RTC prescalar set to 8									*/
	RCC->CFGR |= RCC_CFGR_PPRE2_DIV2;		/* APB2 (high speed, can't exceed 90 MHz) divided by 2		*/
	RCC->CFGR |= RCC_CFGR_PPRE1_DIV4;		/* APB1 (low speed, can't exceed 45 MHz) clock divided by 4	*/
	RCC->CFGR |= RCC_CFGR_HPRE_DIV1;		/* AHB prescalar set to 0 									*/
		
	/* enable high-speed external oscillator */
	RCC->CR |= RCC_CR_HSEBYP;					/* set HSE_BYP, nucleo 144 uses 8 MHz signal from onboard ST-Link	*/
	RCC->CR |= RCC_CR_HSEON;					/* set HSE_ON to enable this clock source							*/
	while (!(RCC->CR & (RCC_CR_HSERDY))) {;}	/* poll HSE_RDY														*/
		
	/* enable PLL */
	RCC->CR |= RCC_CR_PLLON;					/* set PLL_ON	*/
	while (!(RCC->CR & (RCC_CR_PLLRDY))) {;}	/* poll PLL_RDY	*/
		
	/* switch to PLL as system clock */
	RCC->CFGR |= RCC_CFGR_SW_PLL;				/* request switch to PLL		*/
	while (!(RCC_CFGR_SWS_PLL)) {;}				/* wait for PLL to be source	*/
		
	/* update core clock variable */
	SystemCoreClockUpdate();
		
	/* setup SysTick timer, 1ms interrupts */
	SysTick_Config(SystemCoreClock / 1000);
}
